#include "AssetManager.h"
#include "Components.h"

AssetManager::~AssetManager()
{
	for (auto t : textures)
	{
		SDL_DestroyTexture(t.second);
	}
	textures.clear();
}

AssetManager& AssetManager::GetInstance()
{
	static AssetManager instance;
	return instance;
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::CreateProjectile(Vector2D position, int direction, int speed, std::string id, CollisionTag _tag)
{
	auto& projectile(EntityManager::GetInstance().AddEntity(id));
	projectile.AddComponent<TransformComponent>(position.x, position.y, 64, 64, false);
	projectile.AddComponent<SpriteComponent>(id);
	projectile.AddComponent<ProjectileComponent>(direction, speed);
	projectile.AddComponent<ColliderComponent>(_tag);
	projectile.GetComponent<ColliderComponent>().SetCollisionVisibility(true);
	projectile.AddGroup(Projectile);
}

SDL_Texture* AssetManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void AssetManager::Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}
