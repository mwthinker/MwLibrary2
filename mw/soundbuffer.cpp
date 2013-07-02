#include "soundbuffer.h"

#include <SDL_mixer.h>
#include <iostream>

namespace mw {

	int SoundBuffer::nbrOfInstances_ = 0;

	std::map<int,int> SoundBuffer::channelList_;

	SoundBuffer::SoundBuffer(std::string filename) {
		mixChunk_ = 0;
		if (nbrOfInstances_ < 1) {
			//Mix_Init(MIX_INIT_MP3);

			int success = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
			if (success == -1) {
				std::cout << "\n" << "Sound failed to initiate, error: " << Mix_GetError() << "\n";
			} else {
				std::cout << "\n" << "Sound succeeded to initiate!" << "\n";
			}
		}
		++nbrOfInstances_;

		mixChunk_ = Mix_LoadWAV(filename.c_str());

		if (mixChunk_ == 0) {
			std::cout << "\n" << filename << " failed to load!\n";
		} else {
			std::cout << "\n" << filename << " loaded successfully!\n";
		}
	}

	SoundBuffer::~SoundBuffer() {
		if (mixChunk_ != 0) {
			Mix_FreeChunk(mixChunk_);
		}

		--nbrOfInstances_;
		if (nbrOfInstances_ < 1) {
			Mix_CloseAudio();
			//Mix_Quit();
		}
	}

} // Namespace mw
