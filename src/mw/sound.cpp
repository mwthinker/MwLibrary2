#include "sound.h"

#include <iostream>
#include <algorithm>

namespace mw {

	int Sound::lastId_ = 0;

	Sound::Sound() {
		channel_ = -1;
		id_ = ++lastId_;
	}

	Sound::Sound(std::string filename) {
		soundBuffer_ = std::make_shared<SoundBuffer>(filename);
		channel_ = -1;
		id_ = ++lastId_;
	}
	
	Sound::Sound(const Sound& sound) {
		soundBuffer_ = sound.soundBuffer_;
		channel_ = -1;
		id_ = ++lastId_;
	}

	Sound& Sound::operator=(const Sound& sound) {
		soundBuffer_ = sound.soundBuffer_;
		channel_ = -1;
		id_ = ++lastId_;
		return *this;
	}

	void Sound::play(int loops) {
		if (soundBuffer_ != 0) {
			bool ownChannel = (channel_ != -1 && SoundBuffer::channelList[channel_] == id_);
			bool playing = isPlaying();

			// Have no chanel? Or has stopped played the sound?
			if (!ownChannel || !playing) {
				channel_ = Mix_PlayChannel(-1, soundBuffer_->mixChunk_, loops);
				if (channel_ != -1) {
					SoundBuffer::channelList[channel_] = id_;
				} else {
					// All channels is being used.
					std::cerr << "\nFailed to play sound, id " << id_ << ", all channels is being used!\n";
					std::cerr << Mix_GetError() << std::endl;
				}
			} else {
				std::cerr << "\nFailed to play sound, id " << id_ << ", already playing";
			}
		}
	}

	void Sound::pause() {
		if (soundBuffer_ != 0) {
			// Owns the channel?
			if (SoundBuffer::channelList[channel_] == id_) {
				Mix_Pause(channel_);
			}
		}
	}

	void Sound::resume() {
		if (soundBuffer_ != 0) {
			// Owns the channel?
			if (SoundBuffer::channelList[channel_] == id_) {
				Mix_Resume(channel_);
			}
		}
	}

	bool Sound::isPaused() const {
		if (soundBuffer_ != 0) {
			// Owns the channel?
			if (SoundBuffer::channelList[channel_] == id_) {
				return Mix_Paused(id_) == 1;
			}
		}
		return false;
	}

	int Sound::getChannel() const {
		// Owns the channel?
		if (SoundBuffer::channelList[channel_] == id_) {
			return channel_;
		}
		return 0;
	}

	std::map<int, int> Sound::SoundBuffer::channelList;

	Sound::SoundBuffer::SoundBuffer(std::string filename) : valid_(true) {
		mixChunk_ = Mix_LoadWAV(filename.c_str());
		std::cerr << filename + " failed to load!";
	}

	Sound::SoundBuffer::~SoundBuffer() {
		if (mixChunk_ != 0) {
			// Posible memory leak!
			//Mix_FreeChunk(mixChunk_); // Always fails under Windows.
		}
	}

} // Namespace mw.
