#ifndef MW_SOUND_H
#define MW_SOUND_H

#include "soundbuffer.h"

#include <string>
#include <map>

namespace mw {

	class Sound {
	public:
		Sound();
		Sound(std::string filename);
		Sound(SoundBufferPtr soundBuffer);

		Sound(const Sound& sound);
		Sound& operator=(const Sound& sound);

		void play(int loops = 0);
		
		void pause();
		void resume();

		bool isPaused() const;		

		inline const SoundBufferPtr getSoundBuffer() const {
			return soundBuffer_;
		}

		// Returns the sounds channel. If no channel is own 0 is returned.
		int getChannel() const;

	private:
		int channel_;
		int id_;
		SoundBufferPtr soundBuffer_;

		static int lastId_;
	};

} // Namespace mw.

#endif // MW_SOUND_H
