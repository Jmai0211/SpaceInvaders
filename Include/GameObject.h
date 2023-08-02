#pragma once
#include "SDL.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, const char* bulletTextureSheet, int x, int y);
	~GameObject();

	virtual void Update();
	void Render();
	void Move();
	void Shoot();
	void Clear();
	bool TakeDamage();

	int movementDirection = 1;
	int movementSpeed = 3;

	int bulletDirection = 1;
	int bulletSpeed = 7;

	int health;

	SDL_Rect destRect;
	SDL_Rect bulletDestRect;

	bool isShotActive = false;

private:
	SDL_Texture* objTexture;
	SDL_Texture* bulletTexture;
};

