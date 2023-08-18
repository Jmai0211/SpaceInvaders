#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>

class ColliderComponent;
class GameManager;
class AssetManager;
class Entity;
class MainMenu;

class Game
{
public:
	enum GroupLabels : std::size_t
	{
		groupMap,
		groupEnemy,
		groupPlayer,
		groupProjectile,
	};

	void Init(const char* title, int xPos, int yPos);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	void SetUpLevel();

	static void AddTile(int srcX, int srcY, int xPos, int yPos);

	static void RemoveCollider(ColliderComponent* collider);

	// reset all game data and re spawn player and enemies
	void Restart();

	static SDL_Renderer* renderer;
	static SDL_Window* window;

	static std::vector<ColliderComponent*> colliders;
	static AssetManager* aManager;
	static MainMenu menu;
	static Entity* player;
private:
	void SpawnPlayer();
	void SpawnEnemy();
	void RemoveEnemy(Entity* enemy);
};