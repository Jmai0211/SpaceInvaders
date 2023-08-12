#pragma once
#include "Game.h"
#include "GameManager.h"
#include "TextManager.h"
#include "InputManager.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

Game* game = nullptr;

int main(int argc, char *argv[]) 
{
	// load settings at start
	GameManager::GetInstance().LoadSettings();

	GameManager::GetInstance().LoadGame();

	// limit fps
	const int TargetFPS = 60;
	const int frameDelay = 1000 / TargetFPS;

	Uint32 frameStart;
	int frameTime;

	// create game window
	game = new Game();

	game->Init(TextManager::GetLocalizedText("Space Invaders"), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	// detect controller
	if (SDL_NumJoysticks() > 0 && InputManager::GetController() == nullptr)
	{
		InputManager::SetController(SDL_GameControllerOpen(0));

		if (InputManager::GetController() != nullptr)
		{
			std::cout << "Controller connected" << std::endl;
		}
		else
		{
			std::cout << "Controller not found" << std::endl;
		}
		InputManager::SetControl(InputManager::Control::Controller);
	}

	// game loop
	while (GameManager::GetInstance().GetActiveGame())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();

		game->Update();

		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	SDL_GameControllerClose(InputManager::GetController());
	return 0;
}