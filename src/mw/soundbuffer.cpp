#include "soundbuffer.h"

#include <iostream>

namespace mw {

	InitSoundBuffer::InitSoundBuffer() {
		if (nbrOfInstances < 1) {
			int success = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
			Mix_AllocateChannels(16);
			if (success == -1) {
				std::cerr << "\nSound failed to initiate!";
			}
		}
		++nbrOfInstances;
	}

	InitSoundBuffer::~InitSoundBuffer() {
		--nbrOfInstances;
		if (nbrOfInstances < 1) {
			Mix_CloseAudio();
		}
	}	

	int InitSoundBuffer::nbrOfInstances = 0;

	std::unordered_map<int, int> SoundBuffer::channelList;

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
