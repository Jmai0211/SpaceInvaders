#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>
#include "GameManager.h"

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
private:
};