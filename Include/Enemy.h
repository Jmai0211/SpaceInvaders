#pragma once
#include "SDL.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(const char* textureSheet, const char* bulletTextureSheet, int x, int y, int _health);

	// enemy info
	int baseScore;

	// bullet info
	int coolDown = 0;
	int shootCoolDown = 100;

	SDL_Rect bulletRect;

	bool RandomChance(int probability);

	void Update() override;
private:
	int enemyDirection = 1;
	int movementSpeed = 3;

	int fireChance = 30;
	int bulletSpeed = 5;
};