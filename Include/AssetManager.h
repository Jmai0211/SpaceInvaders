#pragma once
#include <map>
#include <string>
#include <TextureManager.h>
#include "Vector2D.h"
#include "ECS.h"

class AssetManager
{
public:

	// texture management
	void AddTexture(std::string id, const char* path);

	SDL_Texture* GetTexture(std::string id);

	// CreateProjectile function now accepts a position, direction, and speed
	void CreateProjectile(Vector2D position, int direction, int speed);

private:
	EntityManager* eManager;
	std::map<std::string, SDL_Texture*> textures;

	// Internal function to create the projectile entity
	void CreateProjectileInternal(Vector2D position, int direction, int speed);
};