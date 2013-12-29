#ifndef MW_JOYSTICK_H
#define MW_JOYSTICK_H

#include "initsdl.h"

#include <SDL.h>
#include <memory>
#include <string>
#include <vector>

namespace mw {

	class Joystick;
	typedef std::shared_ptr<Joystick> JoystickPtr;

	class Joystick : public InitSdl {
	public:
		~Joystick();

		Joystick(const Joystick&) = delete;
		Joystick& operator=(const Joystick&) = delete;

		// Sets the joystick active, i.e. the joystick is able to trigger sdl events.
		void setActive(bool active);

		// Return if the joystick is active, i.e. if the joystick is able to trigger sdl events.
		bool isActive() const;

		// Return the name of the joystick.
		std::string getName() const;

		// Return all joysticks. A window must bee active.
		static const std::vector<JoystickPtr>& getJoystics();

		// Get the underlaying pointer. Use with care.
		inline SDL_Joystick* getSdlJoystick() const {
			return joystick_;
		}

		inline SDL_JoystickID getJoysticsId() const {
			return SDL_JoystickInstanceID(joystick_);
		}

	private:
		Joystick(int joysticksIndex);

		SDL_Joystick* joystick_;
		int joysticksIndex_;

		static bool firstTime;
		static std::vector<JoystickPtr> joysticks;
	};

} // Namespace mw.

#endif // JOYSTICK_H
