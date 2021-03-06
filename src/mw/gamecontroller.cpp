#include "gamecontroller.h"

#include <SDL.h>

#include <iostream>
#include <algorithm>

namespace mw {

	std::vector<GameControllerPtr> GameController::gameControllers;

	GameController::GameController(SDL_GameController* gameController) {
		gameController_ = gameController;
	}

	GameController::~GameController() {
		if (gameController_ != 0) {
			SDL_GameControllerClose(gameController_);
		}
	}

	std::string GameController::getName() const {
		return SDL_GameControllerName(gameController_);
	}

	const std::vector<GameControllerPtr>& GameController::getGameControllers() {
		return gameControllers;
	}

	GameControllerPtr GameController::addController(int index) {
		GameControllerPtr gameController = nullptr;
		if (SDL_IsGameController(index)) {
			SDL_GameController* controller = SDL_GameControllerOpen(index);
			if (controller) {
				if (gameControllers.empty()) {
					SDL_JoystickEventState(SDL_ENABLE);
				}
				gameController = std::shared_ptr<GameController>(new GameController(controller));
				gameControllers.push_back(gameController);
			} else {
				std::cerr << "Could not open gamecontroller " << ": " << SDL_GetError() << std::endl;
			}
		} else {
			std::cerr << "Game Controller mapping is not avvailable." << std::endl;
		}
		return gameController;
	}

	GameControllerPtr GameController::removeController(SDL_JoystickID instanceId) {
		auto it = std::find_if(gameControllers.begin(), gameControllers.end(), [instanceId](const GameControllerPtr& gameController) {
			return gameController->getInstanceId() == instanceId;
		});
		if (it == gameControllers.end()) {
			return nullptr;
		}
		GameControllerPtr gameController = *it;
		gameControllers.erase(it);
		if (gameControllers.empty()) {
			SDL_JoystickEventState(SDL_DISABLE);
		}
		return gameController;
	}

	void GameController::loadAddGameControllerMappings(std::string file) {
		if (SDL_GameControllerAddMappingsFromFile(file.c_str()) < 0) {
			std::cerr << "Failed to load game controller mappings from file, " << file << ". Error: " << SDL_GetError() << std::endl;
		}
	}
}
