#pragma once
#include <map>
#include <string>
#include <TextureManager.h>
#include "Vector2D.h"
#include "ECS.h"

class AssetManager
{
public:
	AssetManager(EntityManager* man);

	~AssetManager();

	// game objects
	void CreateProjectile(Vector2D position, int direction, int speed, std::string id);

	// texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	EntityManager* eManager;
	std::map<std::string, SDL_Texture*> textures;
};