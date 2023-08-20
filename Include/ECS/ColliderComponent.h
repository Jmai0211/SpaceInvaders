#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include <functional>

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;
	bool destroyed = false;

	TransformComponent* transform;

	// constructor with collider box the same as the asset
	ColliderComponent(std::string _tag)
	{
		tag = _tag;
		texture = TextureManager::LoadTexture("Assets/CollisionBox.png");
	}

	~ColliderComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void Init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 80;
		srcRect.h = 80;

		collider.w = static_cast<int>(transform->Size.x);
		collider.h = static_cast<int>(transform->Size.y);

		destRect.w = transform->Size.x;
		destRect.h = transform->Size.y;
	}

	void Update() override
	{
		collider.x = static_cast<int>(transform->Position.x);
		collider.y = static_cast<int>(transform->Position.y);

		destRect.x = transform->Position.x;
		destRect.y = transform->Position.y;
	}

	void Render() override
	{
		if (collisionVisible)
		{
			TextureManager::Render(texture, srcRect, destRect);
		}
	}

	void SetCollisionVisibility(bool visible)
	{
		collisionVisible = visible;
	}

private:
	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Rect srcRect;
	bool collisionVisible = false;
};