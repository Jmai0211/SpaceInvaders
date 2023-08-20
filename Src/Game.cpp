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
#include "CollisionManager.h"
#include "Map.h"
#include "GameManager.h"
#include "AssetManager.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;

MainMenu Game::menu;
Map* map;
EntityManager& Game::eManager = EntityManager::GetInstance();

Entity* Game::player;

AssetManager* Game::aManager;

void Game::Init(const char* title, int xPos, int yPos)
{
	// fullscreen information
	int flags = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized!" << std::endl;

		SDL_Surface* iconSurface = IMG_Load("Assets/Logo.png");

		// create a window
		window = SDL_CreateWindow(title, xPos, yPos, GameManager::GetInstance().GetResolution().first, GameManager::GetInstance().GetResolution().second, flags);
		
		if (window)
		{
			std::cout << "Window created!" << std::endl;

			// set window icon
			SDL_SetWindowIcon(window, iconSurface);
		}

		// create a renderer with black background
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		GameManager::GetInstance().SetActiveGame(true);

		TextManager::Init();

		aManager = new AssetManager();

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
	// load game textures
	aManager->AddTexture("Player", "Assets/Player.png");

	aManager->AddTexture("Enemy", "Assets/Enemy1.png");

	aManager->AddTexture("PlayerBullet", "Assets/PlayerBullet.png");

	aManager->AddTexture("EnemyBullet", "Assets/EnemyBullet.png");

	SpawnPlayer();

	SpawnEnemy();

	TextManager::AddText(200, 70, std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str(), TextManager::GetFont("Normal"), "Score");

	TextManager::AddText(960, 70, std::string(TextManager::GetLocalizedText("Record: ")).append(std::to_string(GameManager::GetInstance().GetHighScore())).c_str(), TextManager::GetFont("Normal"), "Record");

	TextManager::AddText(1720, 70, std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->GetComponent<PlayerComponent>().GetHealth())).c_str(), TextManager::GetFont("Normal"), "Health");
	
	GameManager::GetInstance().SetState(GameManager::GameState::Playing);
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(eManager.AddEntity("Tile"));

	tile.AddComponent<TileComponent>(srcX, srcY, xPos, yPos, "Map");

	tile.AddGroup(groupMap);
}

void Game::GameOver()
{
	GameManager::GetInstance().SaveGame();
	GameManager::GetInstance().SetState(GameManager::GameState::GameOver);
	TextManager::AddText(960, 540, TextManager::GetLocalizedText("Game Over"), TextManager::GetFont("Large"), "GameOver");

	switch (InputManager::GetControl())
	{
	case InputManager::Control::Keyboard:
		TextManager::AddText(960, 680, TextManager::GetLocalizedText("Press ESC to restart"), TextManager::GetFont("Small"), "Restart");
		break;
	case InputManager::Control::Controller:
		TextManager::AddText(960, 680, TextManager::GetLocalizedText("Press A to restart"), TextManager::GetFont("Small"), "Restart");
		break;
	default:
		break;
	}

	std::vector<Entity*> temp = eManager.FindEntitiesWithSubstring("");

	// destroy all remaining entities
	for (auto c : temp)
	{
		c->Destroy();
	}
}

void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// close the window
		case SDL_QUIT:
			Clean();
			GameManager::GetInstance().SetActiveGame(false);
			break;
		// when the controller connected
		case SDL_CONTROLLERDEVICEADDED:
			InputManager::SetController(SDL_GameControllerOpen(0));
			InputManager::SetControl(InputManager::Control::Controller);
			break;
		// when the controller disconnected
		case SDL_CONTROLLERDEVICEREMOVED:
			SDL_GameControllerClose(InputManager::GetController());
			InputManager::SetController(nullptr);
			InputManager::SetControl(InputManager::Control::Keyboard);
			break;
		// when the player presses a key on the keyboard, switch control mode over to keyboard control
		case SDL_KEYDOWN:
			if (InputManager::GetControl() == InputManager::Control::Controller)
			{
				InputManager::SetControl(InputManager::Control::Keyboard);
			}
			InputManager::InputKeyDown();
			break;
		// when the player presses a button or pushes a joystick on the controller, switch control mode over to controller control
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERAXISMOTION:
			if (InputManager::GetControl() == InputManager::Control::Keyboard)
			{
				InputManager::SetControl(InputManager::Control::Controller);
			}
			InputManager::InputKeyDown();
			break;
		case SDL_KEYUP:
			InputManager::InputKeyUp();
			break;
		case SDL_CONTROLLERBUTTONUP:
			InputManager::InputKeyUp();
		default:
			break;
		}
	}
}

void Game::Update()
{
	std::vector<Entity*> temp;
	InputManager::InputHold();
	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Playing:
		eManager.ProcessEntityAdditions();
		eManager.Update();
		eManager.Refresh();
		CollisionManager::Update();
		break;
	case GameManager::GameState::GameOver:
		eManager.Refresh();
		break;
	default:
		break;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	auto& tilesGroup(eManager.GetGroup(groupMap));
	auto& enemyGroup(eManager.GetGroup(groupEnemy));
	auto& playerGroup(eManager.GetGroup(groupPlayer));
	auto& projectileGroup(eManager.GetGroup(groupProjectile));

	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
	case GameManager::GameState::Option:
		break;
	case GameManager::GameState::Playing:
		for (auto& t : tilesGroup)
		{
			t->Render();
		}
		for (auto& e : enemyGroup)
		{
			e->Render();
		}
		for (auto& p : playerGroup)
		{
			p->Render();
		}
		for (auto & p : projectileGroup)
		{
			p->Render();
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
	delete aManager;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::SpawnPlayer()
{
	player = &eManager.AddEntity("Player");

	// add transform component for position and scale
	player->AddComponent<TransformComponent>(960, 1000, 96, 96);

	// add sprite component for rendering sprites
	player->AddComponent<SpriteComponent>("Player");

	// add player input component to allow the player to receive input
	player->AddComponent<PlayerComponent>(5);

	player->AddComponent<ColliderComponent>("Player");

	player->AddGroup(groupPlayer);
}

void Game::SpawnEnemy()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			// Create a new enemy entity and store a reference to it in the vector
			Entity& enemy = eManager.AddEntity("Alien");

			// Add a TransformComponent to the enemy entity
			enemy.AddComponent<TransformComponent>(100 + x * 120, 200 + y * 120, 80, 80);

			enemy.AddComponent<SpriteComponent>("Enemy");

			enemy.AddComponent<ColliderComponent>("Enemy");

			enemy.AddComponent<EnemyAIComponent>(1 + static_cast<int>(LevelManager::GetDifficulty() / 5), 3 + LevelManager::GetDifficulty());

			enemy.SetDestroyEnemyCallback([this](Entity* enemy) {
				CheckEnemySpawn();
				});

			enemy.AddGroup(groupEnemy);
		}
	}
}

void Game::CheckEnemySpawn()
{
	std::vector<Entity*> temp = eManager.FindEntitiesWithSubstring("Alien");
	if (temp.empty() && GameManager::GetInstance().GetState() == GameManager::GameState::Playing)
	{
		LevelManager::SetDifficulty(LevelManager::GetDifficulty() + 1);
		EntityManager::GetInstance().QueueEntityToAdd([this]() {
			SpawnEnemy();
		});
	}
}

void Game::Restart()
{
	GameManager::GetInstance().SetState(GameManager::GameState::Playing);
	TextManager::UnRegisterText("GameOver");
	TextManager::UnRegisterText("Restart");
	LevelManager::SetDifficulty(1);
	SpawnPlayer();
	SpawnEnemy();
	TextManager::textArray["Health"]->UpdateText(std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->GetComponent<PlayerComponent>().GetHealth())).c_str());
	GameManager::GetInstance().SetScore(0);
	TextManager::textArray["Score"]->UpdateText(std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());
}