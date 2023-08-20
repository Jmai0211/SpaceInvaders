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

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::CreateProjectile(Vector2D position, int direction, int speed, std::string id)
{
	// Queue the creation of the projectile entity
	EntityManager::GetInstance().QueueEntityToAdd([this, position, direction, speed, id]() {
		CreateProjectileInternal(position, direction, speed, id);
		});
}

void AssetManager::CreateProjectileInternal(Vector2D position, int direction, int speed, std::string id)
{
	auto& projectile(EntityManager::GetInstance().AddEntity("Projectile"));
	projectile.AddComponent<TransformComponent>(position.x, position.y, 64, 64, false);
	projectile.AddComponent<SpriteComponent>(id);
	projectile.AddComponent<ProjectileComponent>(direction, speed);
	projectile.AddComponent<ColliderComponent>("Projectile");
	projectile.GetComponent<ColliderComponent>().SetCollisionVisibility(true);
	projectile.AddGroup(Game::groupProjectile);
}
