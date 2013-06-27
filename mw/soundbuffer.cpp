#include "soundbuffer.h"

namespace mw {

	int SoundBuffer::nbrOfInstances_ = 0;

	std::map<int,int> SoundBuffer::channelList_;

	SoundBuffer::SoundBuffer(std::string filename) {
		mixChunk_ = 0;
		if (nbrOfInstances_ < 1) {
			int success = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
			//channelList_[-1] = -2;
			if (success == -1) {
				//throw SdlGameException(Mix_GetError());
				std::cout << "\n" << "Sound failed to initiate!";
			} else {
				std::cout << "\n" << "Sound succeeded to initiate!";
			}
		}
		++nbrOfInstances_;

		mixChunk_ = Mix_LoadWAV(filename.c_str());

		if (mixChunk_ == 0) {
			//printf("\nFailed to load, code: %s\n", Mix_GetError());
			// handle error
			std::cout << "\n" << filename << " failed to load!";
		} else {
			std::cout << "\n" << filename << " Loaded successfully!";
		}
	}

	SoundBuffer::~SoundBuffer() {
		if (mixChunk_ != 0) {
			Mix_FreeChunk(mixChunk_);
		}

		--nbrOfInstances_;
		if (nbrOfInstances_ < 1) {
			Mix_CloseAudio();
		}
	}

} // Namespace mw
