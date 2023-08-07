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

SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;

Text* scoreText;
Text* healthText;

MainMenu menu;
Map* map;

EntityManager eManager;

Entity& player = eManager.AddEntity();
std::vector<Entity*> enemies;

std::vector<ColliderComponent*> Game::colliders;

enum GroupLabels : std::size_t
{
	groupMap,
	groupEnemy,
	groupPlayer,
};

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
	player.AddComponent<TransformComponent>(960.0f, 1000.0f, 60.0f, 80.0f);

	// add sprite component for rendering sprites
	player.AddComponent<SpriteComponent>("Assets/Character.png", 4, 25, 4, 4, 200);

	// add stat component for health and movement speed
	player.AddComponent<StatComponent>(5, 7);

	// add player input component to allow the player to receive input
	player.AddComponent<PlayerInputComponent>();

	player.AddComponent<ColliderComponent>("Player");

	player.GetComponent<ColliderComponent>().SetCollisionVisibility(true);

	player.AddGroup(groupPlayer);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			// Create a new enemy entity and store a reference to it in the vector
			Entity& enemy = eManager.AddEntity();
			enemies.push_back(&enemy);

			// Add a TransformComponent to the enemy entity
			enemy.AddComponent<TransformComponent>(100.0f + x * 120.0f, 200.0f + y * 120.0f, 80.0f, 80.0f);

			enemy.AddComponent<SpriteComponent>("Assets/Enemy1.png");

			enemy.AddComponent<StatComponent>(1, 5);

			enemy.AddComponent<ColliderComponent>("Enemy");

			enemy.GetComponent<ColliderComponent>().SetCollisionVisibility(true);

			enemy.AddComponent<EnemyAIComponent>();

			enemy.AddGroup(groupEnemy);
		}
	}

	scoreText = TextManager::AddText(200, 70, std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());

	healthText = TextManager::AddText(1720, 70, std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player.GetComponent<StatComponent>().Health())).c_str());

	Map::LoadMap("Assets/test.map", 30, 30);
	
	GameManager::GetInstance().SetState(GameManager::GameState::Playing);
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(eManager.AddEntity());

	tile.AddComponent<TileComponent>(x, y, 64, 64, id);

	tile.AddGroup(groupMap);
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
		case GameManager::GameState::Option:
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

		std::cout << enemies[0]->GetComponent<TransformComponent>().Position.x - enemies[1]->GetComponent<TransformComponent>().Position.x << std::endl;
		// check for all collisions against the player
		for (auto c : colliders)
		{
			if (CollisionManager::CheckCollision(player.GetComponent<ColliderComponent>(), *c))
			{

			}
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

	auto& tilesGroup(eManager.GetGroup(groupMap));
	auto& enemyGroup(eManager.GetGroup(groupEnemy));
	auto& playerGroup(eManager.GetGroup(groupPlayer));

	switch (GameManager::GetInstance().GetState())
	{
	case GameManager::GameState::Menu:
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

		LevelManager::Render();
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	LevelManager::Clean();
	SDL_Quit();
}