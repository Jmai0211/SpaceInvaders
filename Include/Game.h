#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>
#include "GameManager.h"

class Player;
class Enemy;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	// graphics
	static SDL_Renderer* renderer;

	// player
	static Player* player;

	// enemy
	static std::vector<Enemy*> enemies;

	void SetUpLevel();

private:
};