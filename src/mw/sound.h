#ifndef MW_SOUND_H
#define MW_SOUND_H

#include "initmixer.h"

#include <string>
#include <map>
#include <memory>

namespace mw {

	class Sound {
	public:
		// Creates a empty sound. Does nothing, but is safe to use as
		// a regular sound, but no sound will be heared.
		Sound();

		~Sound();

		// Loads a soundfile and creates a sound.
		Sound(std::string filename);

		// Copie the sound. Is a fast copy. Will point to the 
		// same Mix_Chunk data.
		Sound(const Sound& sound);
		
		// Copies the sound. Is a fast copy. Will point to the 
		// same Mix_Chunk data.
		Sound& operator=(const Sound& sound);

		// Play the sound one time plus the "loops" variable.
		void play(int loops = 0);

		// Pauses the sound.
		void pause();
		
		// The sound is resumed playing, i.e. if the sound is paused.
		void resume();

		// Return true if the sound is paused else false.
		bool isPaused() const;

		// Stop the playing of the sound.
		void stopPlaying();

		// Set the volume. A value between [0,1].
		void setVolume(float volume);

		// Get the volume. A value between [0,1].
		float getVolume() const;

		// Use with care! Return the pointer to the Mix_Chunk data.
		inline Mix_Chunk* getMixChunk() const {
			return soundBuffer_ ? soundBuffer_->mixChunk_ : nullptr;
		}

		// Return true if the sound points to a soundfile in memory.
		// Else false.
		bool isValid() const;

	private:
		class SoundBuffer;
		typedef std::shared_ptr<SoundBuffer> SoundBufferPtr;

		class SoundBuffer : public InitMixer {
		public:
			SoundBuffer(std::string filename);
			~SoundBuffer();

			Mix_Chunk* mixChunk_;
			bool valid_;
			std::string error_;

			static std::map<int, int> channelList;// <channel, sound id>
		};

		// Returns the sounds channel. If no channel is own 0 is returned.
		int getChannel() const;

		inline bool isPlaying() const {
			return !(channel_ != -1 && Mix_Playing(channel_) != 1);
		}

		inline bool ownChannel() const {
			return (channel_ != -1 && SoundBuffer::channelList[channel_] == id_);
		}

		float volume_;
		int channel_;
		int id_;
		SoundBufferPtr soundBuffer_;

		static int lastId_;
	};

} // Namespace mw.

#endif // MW_SOUND_H
