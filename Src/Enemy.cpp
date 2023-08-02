#include "Enemy.h"
#include <random>
#include <iostream>

Enemy::Enemy(const char* textureSheet, const char* bulletTextureSheet, int x, int y, int _health) : GameObject(textureSheet, bulletTextureSheet, x, y)
{
	health = _health;
	baseScore = health;

	// set enemy bullet sprite info
	bulletRect.h = 16;
	bulletRect.w = 16;

	bulletSpeed = 5;
}

// get random chance for shooting
bool Enemy::RandomChance(int probability)
{
	return (rand() % 100) < probability;
}

// update function
void Enemy::Update()
{
	GameObject::Update();
	Move();

	// handle movement direction
	if (destRect.x <= 0 || destRect.x + destRect.w >= GameManager::GetInstance().GetResolution().first)
	{
		movementDirection *= -1;
	}

	// random chance to shoot
	coolDown++;
	if (coolDown >= shootCoolDown)
	{
		if (RandomChance(fireChance))
		{
			Shoot();
		}
		shootCoolDown = rand() % 200 + 100;
		coolDown = 0;
	}
}
