#include "AssetManager.h"
#include "Components.h"

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::CreateProjectile(Vector2D position, int direction, int speed)
{
	// Queue the creation of the projectile entity
	EntityManager::GetInstance().QueueEntityToAdd([this, position, direction, speed]() {
		CreateProjectileInternal(position, direction, speed);
		});
}

void AssetManager::CreateProjectileInternal(Vector2D position, int direction, int speed)
{
	auto& projectile(EntityManager::GetInstance().AddEntity());
	projectile.AddComponent<TransformComponent>(position.x, position.y, 64, 64, false);
	projectile.AddComponent<SpriteComponent>("Bullet");
	projectile.AddComponent<ProjectileComponent>(direction, speed);
	projectile.AddComponent<ColliderComponent>("Projectile");
	projectile.GetComponent<ColliderComponent>().SetDestroyCallback([this](ColliderComponent* collider) {
		Game::RemoveCollider(collider);
		});
	projectile.AddGroup(Game::groupProjectile);
}
