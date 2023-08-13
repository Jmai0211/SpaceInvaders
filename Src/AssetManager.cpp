#include "AssetManager.h"
#include "Components.h"

AssetManager::~AssetManager()
{
	for (auto f : fonts)
	{
		TTF_CloseFont(f.second);
	}
	fonts.clear();
	TTF_Quit();

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

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
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
	auto& projectile(EntityManager::GetInstance().AddEntity());
	projectile.AddComponent<TransformComponent>(position.x, position.y, 64, 64, false);
	projectile.AddComponent<SpriteComponent>(id);
	projectile.AddComponent<ProjectileComponent>(direction, speed);
	projectile.AddComponent<ColliderComponent>("Projectile");
	projectile.GetComponent<ColliderComponent>().SetDestroyCallback([this](ColliderComponent* collider) {
		Game::RemoveCollider(collider);
		});
	projectile.AddGroup(Game::groupProjectile);
}
