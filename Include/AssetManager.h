#pragma once
#include <map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "ECS.h"
#include "Enums.h"

class AssetManager
{
public:
	static AssetManager& GetInstance();

	// Load texture from directory
	SDL_Texture* LoadTexture(const char* fileName);

	// Add texture to the map
	void AddTexture(std::string id, const char* path);

	// Return texture from the map
	SDL_Texture* GetTexture(std::string id);

	// Create a projectile entity with its required components
	void CreateProjectile(Vector2D position, int direction, int speed, std::string id, CollisionTag _tag);

	// Render all textures
	void Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);

private:
	AssetManager() = default;
	~AssetManager();
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	std::map<std::string, SDL_Texture*> textures;
};