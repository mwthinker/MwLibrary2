#include "joystick.h"

#include <SDL.h>

namespace mw {

	bool Joystick::firstTime = true;
	std::vector<JoystickPtr> Joystick::joysticks;

	Joystick::Joystick(int joysticksIndex) {
		SDL_JoystickEventState(SDL_ENABLE);
		active_ = false;
		joysticksIndex_ = joysticksIndex;
		joystick_ = 0;
	}
		
	Joystick::~Joystick() {
		if (joystick_ != 0 && SDL_WasInit(SDL_INIT_JOYSTICK)) {
			SDL_JoystickClose(joystick_);
		}
	}

	void Joystick::setActive(bool active) {
		if (active) {
			joystick_ = SDL_JoystickOpen(joysticksIndex_);
		} else {
			SDL_JoystickClose(joystick_);
			joystick_ = 0;
		}
		active_ = active;
	}

	bool Joystick::isActive() const {
		return active_;
	}

	std::string Joystick::getName() const {
		return SDL_JoystickName(joystick_);		
	}

	int Joystick::getJoystickIndex() const {
		return joysticksIndex_;
	}

	const std::vector<JoystickPtr>& Joystick::getJoystics() {
		if (firstTime) {
			firstTime = false;
			// Init joysticks!
			int nbr = SDL_NumJoysticks();
			for (int i = 0; i < nbr; ++i) {
				joysticks.push_back(JoystickPtr(new Joystick(i)));
			}
		}
		return joysticks;
	}
}
