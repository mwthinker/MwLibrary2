#include "soundbuffer.h"

#include <iostream>

namespace mw {

	InitSoundBuffer::InitSoundBuffer() {
		if (nbrOfInstances_ < 1) {
			int success = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
			if (success == -1) {
				std::cout << "\nSound failed to initiate!";
			}
		}
		++nbrOfInstances_;
	}

	InitSoundBuffer::~InitSoundBuffer() {
		--nbrOfInstances_;
		if (nbrOfInstances_ < 1) {
			Mix_CloseAudio();
		}
	}

	InitSoundBuffer::InitSoundBuffer(const InitSoundBuffer&) {
		++nbrOfInstances_;
	}

	InitSoundBuffer& InitSoundBuffer::operator=(const InitSoundBuffer&) {
		++nbrOfInstances_;
		return *this;
	}

	int InitSoundBuffer::nbrOfInstances_ = 0;

	std::unordered_map<int, int> SoundBuffer::channelList_;

	SoundBuffer::SoundBuffer(std::string filename) : valid_(true) {
		mixChunk_ = 0;
		mixChunk_ = Mix_LoadWAV(filename.c_str());
		if (mixChunk_ == 0) {
			error_ = filename + " failed to load!";
		}
	}

	SoundBuffer::~SoundBuffer() {
		if (mixChunk_ != 0) {
			Mix_FreeChunk(mixChunk_);
		}
	}

	bool SoundBuffer::isValid() const {
		return valid_;
	}

	std::string SoundBuffer::getError() const {
		return error_;
	}

} // Namespace mw
