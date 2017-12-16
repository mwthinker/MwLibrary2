#include "music.h"

#include <memory>
#include <iostream>

namespace mw {

	Music::Music() {
		volume_ = 1;
	}

	Music::Music(std::string filename) {
		musicBuffer_ = std::make_shared<MusicBuffer>(filename);
		volume_ = 1;
	}

	void Music::play(int loops) {
		if (musicBuffer_ && musicBuffer_->valid_) {
			setVolume(volume_);
			Mix_PlayMusic(musicBuffer_->mixMusic_, loops);
		}
	}

	void Music::pause() {
		Mix_PausedMusic();
	}

	void Music::resume() {		
		Mix_ResumeMusic();
	}

	bool Music::isPaused() const {
		return Mix_PausedMusic() == 1;
	}
	
	void Music::stopPlaying() {
		Mix_HaltMusic();
	}

	void Music::setVolume(float volume) {
		volume_ = volume;
		Mix_VolumeMusic((int) (volume_ * MIX_MAX_VOLUME));
	}

	float Music::getVolume() const {
		return volume_;
	}

	bool Music::isValid() const {
		return musicBuffer_ ? musicBuffer_->valid_ : false;
	}

	Music::MusicBuffer::MusicBuffer(std::string filename) : valid_(true) {
		mixMusic_ = Mix_LoadMUS(filename.c_str());
		if (mixMusic_ == nullptr) {
			valid_ = false;
			std::cerr << filename + " failed to load!" << std::endl;
		}
	}

	Music::MusicBuffer::~MusicBuffer() {
		if (mixMusic_ != 0) {
			Mix_FreeMusic(mixMusic_);
		}
	}

} // Namespace mw.
