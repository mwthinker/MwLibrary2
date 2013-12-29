#include "joystick.h"

#include <SDL.h>

namespace mw {

	bool Joystick::firstTime = true;
	std::vector<JoystickPtr> Joystick::joysticks;

	Joystick::Joystick(int joysticksIndex) {
		// Only the first time.
		if (firstTime) {
			SDL_InitSubSystem(SDL_INIT_JOYSTICK);
			SDL_JoystickEventState(SDL_ENABLE);
			firstTime = false;
		}

		joysticksIndex_ = joysticksIndex;
		joystick_ = nullptr;
	}

	Joystick::~Joystick() {
		if (joystick_ != 0 && SDL_WasInit(SDL_INIT_JOYSTICK)) {
			SDL_JoystickClose(joystick_);
		}
	}

	void Joystick::setActive(bool active) {
		if (isActive() != active) {
			if (active) {
				joystick_ = SDL_JoystickOpen(joysticksIndex_);
			} else {
				SDL_JoystickClose(joystick_);
				joystick_ = nullptr;
			}
		}
	}

	bool Joystick::isActive() const {
		return SDL_TRUE == SDL_JoystickGetAttached(joystick_);
	}

	std::string Joystick::getName() const {
		return SDL_JoystickName(joystick_);
	}

	const std::vector<JoystickPtr>& Joystick::getJoystics() {
		if (firstTime) {
			// Init joysticks!
			int nbr = SDL_NumJoysticks();
			for (int i = 0; i < nbr; ++i) {
				joysticks.push_back(JoystickPtr(new Joystick(i)));
			}
		}
		return joysticks;
	}

}
