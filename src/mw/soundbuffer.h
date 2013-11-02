#ifndef MW_SOUNDBUFFER_H
#define MW_SOUNDBUFFER_H

#include "initsdl.h"

#include <SDL_mixer.h>

#include <string>
#include <unordered_map>
#include <memory>

namespace mw {

	class SoundBuffer;
	typedef std::shared_ptr<SoundBuffer> SoundBufferPtr;

	class InitSoundBuffer {
	protected:
		InitSoundBuffer();
		~InitSoundBuffer();

		InitSoundBuffer(const InitSoundBuffer&) = delete;
		InitSoundBuffer& operator=(const InitSoundBuffer&) = delete;

	private:
		static int nbrOfInstances;
	};

	class SoundBuffer : public InitSdl, public InitSoundBuffer {
	public:
		friend class Sound;

		SoundBuffer(std::string filename);
		~SoundBuffer();

		// Returns true if everything is correct. Else false.
		bool isValid() const;

		// Returns error message, i.e. when the isValid function returns false.
		// If no error string will be empty.
		std::string getError() const;

		// Use with care! Gets a pointer to the sound data.
		inline Mix_Chunk* getTtfFont() const {
			mixChunk_;
		}

	private:
		Mix_Chunk* mixChunk_;
		bool valid_;
		std::string error_;

		static std::unordered_map<int, int> channelList;// <channel, sound id>
	};

} // Namespace mw.

#endif // MW_SOUNDBUFFER_H
