#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(EntityManager* man) : eManager(man)
{}

AssetManager::~AssetManager()
{
}

void AssetManager::CreateProjectile(Vector2D position, int direction, int speed, std::string id)
{
	auto& projectile(eManager->AddEntity());
	projectile.AddComponent<TransformComponent>(position.x, position.y, 64, 64);
	projectile.AddComponent<SpriteComponent>("Bullet");
	projectile.AddComponent<ProjectileComponent>(direction, speed);
	projectile.AddComponent<ColliderComponent>("Projectile");
	projectile.GetComponent<ColliderComponent>().SetCollisionVisibility(true);
	projectile.GetComponent<ColliderComponent>().SetDestroyCallback([this](ColliderComponent* collider) {
		Game::RemoveCollider(collider);
		});
	//projectile.AddGroup(Game::groupProjectile);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}
