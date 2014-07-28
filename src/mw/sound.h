#ifndef MW_SOUND_H
#define MW_SOUND_H

#include "initmixer.h"

#include <string>
#include <map>
#include <memory>

namespace mw {

	class Sound {
	public:
		Sound();
		Sound(std::string filename);

		Sound(const Sound& sound);
		Sound& operator=(const Sound& sound);

		void play(int loops = 0);

		void pause();
		void resume();

		bool isPaused() const;

		// Use with care! Return the pointer to the Mix_Chunk data.
		inline Mix_Chunk* getMixChunk() const {
			return soundBuffer_ ? soundBuffer_->mixChunk_ : nullptr;
		}

	private:
		class SoundBuffer;
		typedef std::shared_ptr<SoundBuffer> SoundBufferPtr;

		// Returns the sounds channel. If no channel is own 0 is returned.
		int getChannel() const;

		inline bool isPlaying() const {
			return !(channel_ != -1 && Mix_Playing(channel_) != 1);
		}

		class SoundBuffer : public InitMixer {
		public:
			SoundBuffer(std::string filename);
			~SoundBuffer();

			Mix_Chunk* mixChunk_;
			bool valid_;
			std::string error_;

			static std::map<int, int> channelList;// <channel, sound id>
		};

		int channel_;
		int id_;
		SoundBufferPtr soundBuffer_;

		static int lastId_;
	};

} // Namespace mw.

#endif // MW_SOUND_H
