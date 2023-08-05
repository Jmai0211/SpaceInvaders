#include <iostream>
#include <string>
#include "Game.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "TextManager.h"
#include "text.h"
#include "MainMenu.h"
#include "Components.h"

Text* scoreText;
Text* healthText;

MainMenu menu;
EntityManager eManager;

Entity& player = eManager.AddEntity();
std::vector<Entity*> enemies;

Game::Game()
{

}

Game::~Game()
{
	TextManager::CleanUp();
}

void Game::Init(const char* title, int xPos, int yPos)
{
	// fullscreen information
	int flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized!" << std::endl;

		SDL_Surface* iconSurface = IMG_Load("Assets/Logo.png");

		// create a window
		GameManager::GetInstance().SetWindow(SDL_CreateWindow(title, xPos, yPos, GameManager::GetInstance().GetResolution().first, GameManager::GetInstance().GetResolution().second, flags));
		
		if (GameManager::GetInstance().GetWindow())
		{
			std::cout << "Window created!" << std::endl;

			// set window icon
			SDL_SetWindowIcon(GameManager::GetInstance().GetWindow(), iconSurface);
		}

		// create a renderer with black background
		GameManager::GetInstance().SetRenderer(SDL_CreateRenderer(GameManager::GetInstance().GetWindow(), -1, 0));
		if (GameManager::GetInstance().GetRenderer())
		{
			SDL_SetRenderDrawColor(GameManager::GetInstance().GetRenderer(), 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		TextManager::Init();

		GameManager::GetInstance().SetActiveGame(true);

		menu.SetUpMenu();

		SDL_FreeSurface(iconSurface);
	}
	else
	{
		GameManager::GetInstance().SetActiveGame(false);
	}
}

void Game::SetUpLevel()
{
	// add transform component for position and scale
	player.AddComponent<TransformComponent>(960.0f, 1000.0f);

	// add sprite component for rendering sprites
	player.AddComponent<SpriteComponent>("Assets/Player.png");

	// add stat component for health and movement speed
	player.AddComponent<StatComponent>(5, 7);

	// add player input component to allow the player to receive input
	player.AddComponent<PlayerInputComponent>();

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			// Create a new enemy entity and store a reference to it in the vector
			Entity& enemy = eManager.AddEntity();
			enemies.push_back(&enemy);

			// Add a TransformComponent to the enemy entity
			enemy.AddComponent<TransformComponent>(100.0f + x * 120.0f, 200.0f + y * 120.0f);

			enemy.AddComponent<SpriteComponent>("Assets/Enemy1.png");

			enemy.AddComponent<StatComponent>(1, 5);
		}
	}

	std::cout << enemies[0]->GetComponent<TransformComponent>().Position.y;

	scoreText = TextManager::AddText(200, 70, std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());

	healthText = TextManager::AddText(1720, 70, std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player.GetComponent<StatComponent>().Health())).c_str());

	GameManager::GetInstance().SetState(GameManager::GameState::Playing);
}

void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// close window
		case SDL_QUIT:
			GameManager::GetInstance().SetActiveGame(false);
			break;
		// when controller connected
		case SDL_CONTROLLERDEVICEADDED:
			InputManager::SetController(SDL_GameControllerOpen(0));
			InputManager::SetControl(InputManager::Control::Controller);
			break;
		// when controller disconnected
		case SDL_CONTROLLERDEVICEREMOVED:
			SDL_GameControllerClose(InputManager::GetController());
			InputManager::SetController(nullptr);
			InputManager::SetControl(InputManager::Control::Keyboard);
			break;
		default:
			break;
		}

		// handle input
		switch (GameManager::GetInstance().GetState())
		{
		case GameManager::GameState::Menu:
			menu.Input();
			break;
		case GameManager::GameState::Playing:
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
		break;
	case GameManager::GameState::Playing:
		eManager.Update();
		eManager.Refresh();
		//// enemy update function
		//for (size_t i = 0; i < enemies.size(); i++)
		//{
		//	enemies[i]->Update();

		//	// check if enemy bullet hit player
		//	if (enemies[i]->isShotActive)
		//	{
		//		if (CollisionManager::CheckCollision(player->destRect, enemies[i]->bulletDestRect))
		//		{
		//			if (player->TakeDamage())
		//			{
		//				GameManager::GetInstance().SetActiveGame(false);
		//				std::cout << "Game Over!" << std::endl;
		//			}
		//			healthText->UpdateText(std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->health)).c_str());
		//			enemies[i]->isShotActive = false;
		//		}
		//	}

		//	// check if player bullet hit enemy
		//	if (player->isShotActive)
		//	{
		//		if (CollisionManager::CheckCollision(player->bulletDestRect, enemies[i]->destRect))
		//		{
		//			if (enemies[i]->TakeDamage())
		//			{
		//				GameManager::GetInstance().SetScore(GameManager::GetInstance().GetScore() + enemies[i]->baseScore);
		//				enemies.erase(enemies.begin() + i);
		//				scoreText->UpdateText(std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());
		//			}
		//			player->isShotActive = false;
		//		}
		//	}
		//}

		// Tempory: close window after all enemies died
		break;
	case GameManager::GameState::GameOver:
		break;
	default:
		break;
	}
}

void Game::Render()
{
	SDL_RenderClear(GameManager::GetInstance().GetRenderer());

	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
		break;
	case GameManager::GameState::Playing:
		eManager.Render();
		LevelManager::Render();
		break;
	case GameManager::GameState::GameOver:
		break;
	default:
		break;
	}

	// render text
	TextManager::Render();

	SDL_RenderPresent(GameManager::GetInstance().GetRenderer());
}

// destroyed created instances and close window
void Game::Clean()
{
	SDL_DestroyWindow(GameManager::GetInstance().GetWindow());
	SDL_DestroyRenderer(GameManager::GetInstance().GetRenderer());
	LevelManager::Clean();
	SDL_Quit();
}