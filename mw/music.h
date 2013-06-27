#ifndef MW_MUSIC_H
#define MW_MUSIC_H

#include "soundbuffer.h"

#include <string>

namespace mw {

	class Music {
	public:
		Music() {
		}

		void play() {
		}

		void setLoop(bool loop) {
			loop_ = loop;
		}

		bool isLoop() const {
			return loop_;
		}

		void setVolume(bool loop) {
			loop_ = loop;
		}

		bool getVolume() const {
			return loop_;
		}
	private:
		bool loop_;
	};

} // namespace mw

#endif // MW_MUSIC_H
