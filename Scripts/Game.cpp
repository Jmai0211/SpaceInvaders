#include <iostream>
#include <string>
#include "Game.h"
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
#include "AudioManager.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;

MainMenu Game::menu;
EntityManager& eManager = EntityManager::GetInstance();

Entity* Game::player;

AssetManager& aManager = AssetManager::GetInstance();

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

		AudioManager::GetInstance().Init();

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
	AudioManager::GetInstance().StopMusic();
	// load game textures
	aManager.AddTexture("Player", "Assets/Player.png");

	aManager.AddTexture("Enemy", "Assets/Enemy1.png");

	aManager.AddTexture("PlayerBullet", "Assets/PlayerBullet.png");

	aManager.AddTexture("EnemyBullet", "Assets/EnemyBullet.png");

	SpawnPlayer();

	LevelManager::GetInstance().SpawnEnemy();

	TextManager::AddText(200, 70, std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str(), TextManager::GetFont("Normal"), "Score");

	TextManager::AddText(960, 70, std::string(TextManager::GetLocalizedText("Record: ")).append(std::to_string(GameManager::GetInstance().GetHighScore())).c_str(), TextManager::GetFont("Normal"), "Record");

	TextManager::AddText(1720, 70, std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->GetComponent<PlayerComponent>().GetHealth())).c_str(), TextManager::GetFont("Normal"), "Health");
	
	GameManager::GetInstance().SetState(GameState::Playing);

	AudioManager::GetInstance().PlayMusic("GameMusic");
}

void Game::BackToMainMenu()
{
	TextManager::UnRegisterText("Score");
	TextManager::UnRegisterText("Record");
	TextManager::UnRegisterText("Health");
	TextManager::insertionOrder.clear();

	AudioManager::GetInstance().StopMusic();
	AudioManager::GetInstance().PlayMusic("BackgroundMusic");

	std::vector<Entity*> temp = eManager.FindEntitiesWithSubstring("");
	// destroy all remaining entities
	for (auto c : temp)
	{
		c->Destroy();
	}

	GameManager::GetInstance().SetScore(0);

	menu.SetUpMenu();
	
	GameManager::GetInstance().SetState(GameState::Menu);
}

void Game::GameOver()
{
	GameManager::GetInstance().SaveGame();
	GameManager::GetInstance().SetState(GameState::GameOver);
	TextManager::AddText(960, 540, TextManager::GetLocalizedText("Game Over"), TextManager::GetFont("Large"), "GameOver");

	AudioManager::GetInstance().StopMusic();

	switch (InputManager::GetControl())
	{
	case Control::Keyboard:
		TextManager::AddText(960, 680, TextManager::GetLocalizedText("Press ESC to restart"), TextManager::GetFont("Small"), "Restart");
		break;
	case Control::Controller:
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
			InputManager::SetControl(Control::Controller);
			break;
		// when the controller disconnected
		case SDL_CONTROLLERDEVICEREMOVED:
			SDL_GameControllerClose(InputManager::GetController());
			InputManager::SetController(nullptr);
			InputManager::SetControl(Control::Keyboard);
			break;
		// when the player presses a key on the keyboard, switch control mode over to keyboard control
		case SDL_KEYDOWN:
			if (InputManager::GetControl() == Control::Controller)
			{
				InputManager::SetControl(Control::Keyboard);
			}
			InputManager::InputKeyDown();
			break;
		// when the player presses a button or pushes a joystick on the controller, switch control mode over to controller control
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERAXISMOTION:
			if (InputManager::GetControl() == Control::Keyboard)
			{
				InputManager::SetControl(Control::Controller);
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
	InputManager::InputHold();
	switch (GameManager::GetInstance().GetState())
	{
	case GameState::Playing:
		eManager.Refresh();
		eManager.Update();
		CollisionManager::GetInstance().Update();
		break;
	case GameState::GameOver:
		eManager.Refresh();
		break;
	default:
		break;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	auto& tilesGroup(eManager.GetGroup(Tile));
	auto& enemyGroup(eManager.GetGroup(Enemy));
	auto& playerGroup(eManager.GetGroup(Player));
	auto& projectileGroup(eManager.GetGroup(Projectile));

	switch (GameManager::GetInstance().GetState())
	{
	case GameState::Menu:
	case GameState::Option:
		break;
	case GameState::Playing:
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
	case GameState::GameOver:
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::SpawnPlayer()
{
	player = &eManager.AddEntity("Player");

	// add transform component for position and scale
	player->AddComponent<TransformComponent>(960, 960, 96, 96);

	// add sprite component for rendering sprites
	player->AddComponent<SpriteComponent>("Player");

	// add player input component to allow the player to receive input
	player->AddComponent<PlayerComponent>(5);

	player->AddComponent<ColliderComponent>(CollisionTag::Player);

	player->AddGroup(Player);
}

void Game::Restart()
{
	GameManager::GetInstance().SetState(GameState::Playing);
	TextManager::UnRegisterText("GameOver");
	TextManager::UnRegisterText("Restart");
	LevelManager::GetInstance().SetDifficulty(1);
	SpawnPlayer();
	LevelManager::GetInstance().SpawnEnemy();
	TextManager::textArray["Health"]->UpdateText(std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->GetComponent<PlayerComponent>().GetHealth())).c_str());
	GameManager::GetInstance().SetScore(0);
	TextManager::textArray["Score"]->UpdateText(std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());
	AudioManager::GetInstance().PlayMusic("GameMusic");
}