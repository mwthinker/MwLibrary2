#include "sound.h"

#include <iostream>
#include <algorithm>

namespace mw {

	int Sound::lastId_ = 0;

	Sound::Sound() {
		channel_ = -1;
		id_ = ++lastId_;
		volume_ = 1;
	}

	Sound::Sound(std::string filename) {
		soundBuffer_ = std::make_shared<SoundBuffer>(filename);
		channel_ = -1;
		id_ = ++lastId_;
		volume_ = 1;
	}
	
	Sound::Sound(const Sound& sound) {
		soundBuffer_ = sound.soundBuffer_;
		channel_ = -1;
		id_ = ++lastId_;
		volume_ = sound.volume_;
	}

	Sound& Sound::operator=(const Sound& sound) {
		soundBuffer_ = sound.soundBuffer_;
		channel_ = -1;
		id_ = ++lastId_;
		volume_ = sound.volume_;
		return *this;
	}

	void Sound::play(int loops) {
		if (soundBuffer_ && soundBuffer_->valid_) {
			// Have no chanel? Or has stopped played the sound?
			if (!ownChannel() || !isPlaying()) {
				channel_ = Mix_PlayChannel(-1, soundBuffer_->mixChunk_, loops);
				if (channel_ != -1) {
					SoundBuffer::channelList[channel_] = id_;
					// Set the volume on the current channel.
					setVolume(volume_);
				} else {
					// All channels is being used.
					std::cerr << "\nFailed to play sound, id " << id_ << ", all channels is being used!\n";
					std::cerr << Mix_GetError() << std::endl;
				}
			} else {
				std::cerr << "\nFailed to play sound, id " << id_ << ", already playing" << std::endl;
			}
		}
	}

	void Sound::pause() {
		if (soundBuffer_ && soundBuffer_->valid_) {
			// Owns the channel?
			if (SoundBuffer::channelList[channel_] == id_) {
				Mix_Pause(channel_);
			}
		}
	}

	void Sound::resume() {
		if (soundBuffer_ && soundBuffer_->valid_) {
			// Owns the channel?
			if (SoundBuffer::channelList[channel_] == id_) {
				Mix_Resume(channel_);
			}
		}
	}

	bool Sound::isPaused() const {
		if (soundBuffer_ && soundBuffer_->valid_) {
			// Owns the channel?
			if (SoundBuffer::channelList[channel_] == id_) {
				return Mix_Paused(id_) == 1;
			}
		}
		return false;
	}

	void Sound::stopPlaying() {
		if (ownChannel() && isPlaying()) {
			Mix_HaltChannel(channel_);
		}
	}

	void Sound::setVolume(float volume) {
		volume_ = volume;
		if (soundBuffer_ && soundBuffer_->valid_) {
			Mix_Volume(channel_, (int) (volume_ * MIX_MAX_VOLUME));
		}
	}

	float Sound::getVolume() const {
		return volume_;
	}

	bool Sound::isValid() const {
		return soundBuffer_ ? soundBuffer_->valid_ : false;
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
		if (mixChunk_ == nullptr) {
			valid_ = false;
			std::cerr << filename + " failed to load!" << std::endl;
		}
	}

	Sound::SoundBuffer::~SoundBuffer() {
		if (mixChunk_ != 0) {
			Mix_FreeChunk(mixChunk_);
		}
	}

} // Namespace mw.
