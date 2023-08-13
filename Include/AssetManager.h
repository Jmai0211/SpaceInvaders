#pragma once
#include <map>
#include <string>
#include <TextureManager.h>
#include "Vector2D.h"
#include "ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	~AssetManager();
	// texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

	// CreateProjectile function now accepts a position, direction, and speed
	void CreateProjectile(Vector2D position, int direction, int speed, std::string id);

private:
	EntityManager* eManager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;

	// Internal function to create the projectile entity
	void CreateProjectileInternal(Vector2D position, int direction, int speed, std::string id);
};