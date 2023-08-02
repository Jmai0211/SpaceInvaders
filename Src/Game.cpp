#include <iostream>
#include <string>
#include "Game.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Enemy.h"
#include "TextManager.h"
#include "text.h"
#include "MainMenu.h"

SDL_Renderer* Game::renderer = nullptr;
std::vector<Enemy*> Game::enemies;
Player* Game::player;

Text* scoreText;
Text* healthText;

MainMenu menu;

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

		// create a window
		GameManager::GetInstance().SetWindow(SDL_CreateWindow(title, xPos, yPos, GameManager::GetInstance().GetResolution().first, GameManager::GetInstance().GetResolution().second, flags));
		
		if (GameManager::GetInstance().GetWindow())
		{
			std::cout << "Window created!" << std::endl;
		}

		// create a renderer with black background
		renderer = SDL_CreateRenderer(GameManager::GetInstance().GetWindow(), -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		TextManager::Init();

		GameManager::GetInstance().SetActiveGame(true);

		menu.SetUpMenu();
	}
	else
	{
		GameManager::GetInstance().SetActiveGame(false);
	}
}

void Game::SetUpLevel()
{
	// spawn player
	player = new Player("Assets/Player.png", "Assets/Bullet.png", 960, 900, 1000);

	// spawn enemy
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			Enemy* temp;
			if (y == 0)
			{
				temp = new Enemy("Assets/Enemy3.png", "Assets/Bullet.png", (x + 1) * 100, (y + 1) * 100, 3 - y);
			}
			else if (y == 1)
			{
				temp = new Enemy("Assets/Enemy2.png", "Assets/Bullet.png", (x + 1) * 100, (y + 1) * 100, 3 - y);
			}
			else if (y == 2)
			{
				temp = new Enemy("Assets/Enemy1.png", "Assets/Bullet.png", (x + 1) * 100, (y + 1) * 100, 3 - y);
			}
			enemies.push_back(temp);
		}
	}

	scoreText = TextManager::AddText(200, 70, std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());

	healthText = TextManager::AddText(1720, 70, std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->health)).c_str());

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
	}

	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
		menu.Input();
		break;
	case GameManager::GameState::Playing:
		player->Input();
		break;
	default:
		break;
	}
}

void Game::Update()
{
	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
		break;
	case GameManager::GameState::Playing:
		// player update function
		player->Update();

		// enemy update function
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Update();

			// check if enemy bullet hit player
			if (enemies[i]->isShotActive)
			{
				if (CollisionManager::CheckCollision(player->destRect, enemies[i]->bulletDestRect))
				{
					if (player->TakeDamage())
					{
						GameManager::GetInstance().SetActiveGame(false);
						std::cout << "Game Over!" << std::endl;
					}
					healthText->UpdateText(std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->health)).c_str());
					enemies[i]->isShotActive = false;
				}
			}

			// check if player bullet hit enemy
			if (player->isShotActive)
			{
				if (CollisionManager::CheckCollision(player->bulletDestRect, enemies[i]->destRect))
				{
					if (enemies[i]->TakeDamage())
					{
						GameManager::GetInstance().SetScore(GameManager::GetInstance().GetScore() + enemies[i]->baseScore);
						enemies.erase(enemies.begin() + i);
						scoreText->UpdateText(std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());
					}
					player->isShotActive = false;
				}
			}
		}

		// Tempory: close window after all enemies died
		if (enemies.size() <= 0)
		{
			GameManager::GetInstance().SetActiveGame(false);
			std::cout << "Victory" << std::endl;
		}
		break;
	case GameManager::GameState::GameOver:
		break;
	default:
		break;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
		break;
	case GameManager::GameState::Playing:
		// render player
		player->Render();

		// render enemy
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Render();
		}
		break;
	case GameManager::GameState::GameOver:
		break;
	default:
		break;
	}

	// render text
	TextManager::Render();

	SDL_RenderPresent(renderer);
}

// destroyed created instances and close window
void Game::Clean()
{
	SDL_DestroyWindow(GameManager::GetInstance().GetWindow());
	SDL_DestroyRenderer(renderer);
	player->Clear();
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Clear();
	}
	SDL_Quit();
}