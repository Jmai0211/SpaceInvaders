#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "Game.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

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

		Game::colliders.push_back(this);
	}

	void Update() override
	{
		collider.x = static_cast<int>(transform->Position.x);
		collider.y = static_cast<int>(transform->Position.y);
		collider.w = static_cast<int>(transform->Size.x);
		collider.h = static_cast<int>(transform->Size.y);

		destRect.x = collider.x;
		destRect.y = collider.y;
		destRect.w = collider.w;
		destRect.h = collider.h;
	}

	void Render() override
	{
		if (collisionVisible)
		{
			TextureManager::Render(texture, destRect);
		}
	}

	void SetCollisionVisibility(bool visible)
	{
		collisionVisible = visible;
	}

private:
	SDL_Texture* texture;
	SDL_Rect destRect;
	bool collisionVisible = false;
};