#ifndef MW_JOYSTICK_H
#define MW_JOYSTICK_H

#include "initsdl.h"

#include <SDL.h>

#include <memory>
#include <string>
#include <vector>

namespace mw {

	class GameController;
	typedef std::shared_ptr<GameController> GameControllerPtr;

	class GameController : public InitSdl {
	public:
		~GameController();

		GameController(const GameController&) = delete;
		GameController& operator=(const GameController&) = delete;

		// Return the name of the joystick.
		std::string getName() const;

		// Return all gamepads. A window must bee active.
		static const std::vector<GameControllerPtr>& getGameControllers();

		static void loadAddGameControllerMappings(std::string file);

		static GameControllerPtr addController(int index);
		static GameControllerPtr removeController(SDL_JoystickID instanceId);

		// Get the underlaying pointer. Use with care.
		inline SDL_GameController* getSdlGameController() const {
			return gameController_;
		}
		
		// Return the button state.
		inline bool getButtonState(SDL_GameControllerButton button) const {
			return SDL_GameControllerGetButton(gameController_, button) != 0;
		}

		// Return the axis state. Value ranging from -1 and 1. Trigger however range from 0 to 1.
		inline double getAxisState(SDL_GameControllerAxis axis) const {
			return (double) SDL_GameControllerGetAxis(gameController_, axis) / sizeof(Sint16);
		}

		inline bool isAttached() const {
			return SDL_GameControllerGetAttached(gameController_) == SDL_TRUE;
		}

		inline SDL_JoystickID getInstanceId() const {
			return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gameController_));
		}

	private:
		GameController(SDL_GameController* gameController);

		SDL_GameController* gameController_;
		
		static std::vector<GameControllerPtr> gameControllers;
	};

} // Namespace mw.

#endif // JOYSTICK_H
