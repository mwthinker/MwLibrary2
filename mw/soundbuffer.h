#ifndef MW_SOUNDBUFFER_H
#define MW_SOUNDBUFFER_H

#include "initsdl.h"

#include <SDL_mixer.h>

#include <string>
#include <map>
#include <memory>

namespace mw {

	class SoundBuffer : public InitSdl {
	public:
		friend class Sound;

		SoundBuffer(std::string filename);
		~SoundBuffer();

	private:
		SoundBuffer(const SoundBuffer&) {
			// Not to be used. Is not copyable.
		}

		SoundBuffer& operator=(const SoundBuffer&) {
			// Not to be used. Is not copyable.
			return *this;
		}

		Mix_Chunk* mixChunk_;

		static int nbrOfInstances_;		
		static std::map<int,int> channelList_;// <channel, sound id>
	};

	typedef std::shared_ptr<SoundBuffer> SoundBufferPtr;

} // namespace mw

#endif // MW_SOUNDBUFFER_H
