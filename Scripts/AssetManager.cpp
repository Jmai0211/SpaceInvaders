#include "AssetManager.h"
#include "Components.h"

AssetManager::~AssetManager()
{
	// Destroy all loaded textures
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

void AssetManager::CreateProjectile(Entity* parent, int direction, int speed, std::string id, CollisionTag _tag)
{
	auto& projectile(EntityManager::GetInstance().AddEntity(id));

	// Calculate spawn transform information
	int screenWidth = GameManager::GetInstance().GetResolution().first;
	int screenHeight = GameManager::GetInstance().GetResolution().second;

	float widthScale = static_cast<float>(screenWidth) / 1920.0f;
	float heightScale = static_cast<float>(screenHeight) / 1080.0f;

	// Calculate position based on the new size
	int referenceX = static_cast<int>((32) * widthScale);
	int referenceY = static_cast<int>((32) * heightScale);

	int xPos = parent->GetComponent<TransformComponent>().Position.x + parent->GetComponent<TransformComponent>().Size.x / 2 - referenceX;
	int yPos = parent->GetComponent<TransformComponent>().Position.y + parent->GetComponent<TransformComponent>().Size.y / 2 - referenceY;
	projectile.AddComponent<TransformComponent>(xPos, yPos, 64, 64, false);

	projectile.AddComponent<SpriteComponent>(id);
	projectile.AddComponent<ProjectileComponent>(direction, speed);
	projectile.AddComponent<ColliderComponent>(_tag);
	projectile.AddGroup(Projectile);
	AudioManager::GetInstance().PlaySoundEffect("ShootSound");
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
