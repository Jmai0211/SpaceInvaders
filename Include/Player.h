#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "InputManager.h"

class Player : public GameObject
{
public:

	Player(const char* textureSheet, const char* bulletTextureSheet, int x, int y, int health);
	~Player();

	void Input();
	void Update() override;
};

