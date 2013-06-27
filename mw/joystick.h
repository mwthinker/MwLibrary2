#ifndef MW_JOYSTICK_H
#define MW_JOYSTICK_H

#include <SDL.h>
#include <memory>
#include <string>
#include <vector>

namespace mw {
	
	class Joystick;
	typedef std::shared_ptr<Joystick> JoystickPtr;

	class Joystick {
	public:
		Joystick(int joysticksIndex);
		~Joystick();

		// Sets the joystick active, i.e. the joystick is able to trigger sdl events.
		void setActive(bool active);

		// Return if the joystick is active, i.e. if the joystick is able to trigger sdl events.
		bool isActive() const;

		// Return the name of the joystick.
		std::string getName() const;

		// Return the joystick index, which is the number used by sdl to identifie the
		// joystick that triggers an event.
		int getJoystickIndex() const;

		// Returns all joysticks. A window must beeing active.
		static const std::vector<JoystickPtr>& getJoystics();
	
	private:
		Joystick(const Joystick&) {
			// Not to be used. Is not copyable.
		}

		Joystick& operator=(const Joystick&) {
			// Not to be used. Is not copyable.
			return *this;
		}

		SDL_Joystick* joystick_;
		int joysticksIndex_;

		bool active_;

		static bool firstTime;
		static std::vector<JoystickPtr> joysticks;
	};
}

#endif // JOYSTICK_H
