#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>
#include "GameManager.h"

class ColliderComponent;

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

	void SetUpLevel();

	static void AddTile(int id, int x, int y);

	static SDL_Renderer* renderer;
	static SDL_Window* window;

	static std::vector<ColliderComponent*> colliders;
};