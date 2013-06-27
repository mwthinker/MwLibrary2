#include "sound.h"

namespace mw {

	int Sound::lastId_ = 0;

	Sound::Sound() {        
		channel_ = -1;
		id_ = ++lastId_;
	}

	Sound::Sound(std::string filename) {
		soundBuffer_ = SoundBufferPtr(new SoundBuffer(filename));
		channel_ = -1;
		id_ = ++lastId_;
	}

	Sound::Sound(SoundBufferPtr soundBuffer) {
		soundBuffer_ = soundBuffer;
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
			bool ownChannel = (SoundBuffer::channelList_[channel_] == id_);
			bool isPlaying = (ownChannel && channel_ != -1 && Mix_Playing(channel_) != 1);

			if (!ownChannel || isPlaying) {
				channel_ = Mix_PlayChannel(-1, soundBuffer_->mixChunk_, loops);
				if (channel_ != -1) {
					SoundBuffer::channelList_[channel_] = id_;
				} else {
					// All channels is being used.
					std::cout << "\nFailed to play sound, id " << id_ << ",all channels is being used!\n";
					std::cout << Mix_GetError() << std::endl;
				}
			} else {
				std::cout << "\nFailed to play sound, id " << id_ << ", already playing";
			}
		}
	}

	void Sound::pause() {
		if (soundBuffer_ != 0) {
			if (SoundBuffer::channelList_[channel_] == id_) { // Owns the channel
				Mix_Pause(channel_);
			}
		}
	}

	bool Sound::isPaused() const {
		if (soundBuffer_ != 0) {
			if (SoundBuffer::channelList_[channel_] == id_) { // Owns the channel
				return Mix_Paused(id_) == 1;
			}
		}
		return false;
	}

} // Namespace mw
