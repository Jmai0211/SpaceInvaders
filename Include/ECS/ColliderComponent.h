#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "CollisionManager.h"
#include <functional>
#include "ProjectileComponent.h"
#include "EnemyAIComponent.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	CollisionTag tag;

	TransformComponent* transform;

	// constructor with collider box the same as the asset
	ColliderComponent(CollisionTag _tag)
	{
		tag = _tag;
		texture = AssetManager::GetInstance().LoadTexture("Assets/CollisionBox.png");
		CollisionManager::GetInstance().AddCollider(this);
	}

	~ColliderComponent()
	{
		CollisionManager::GetInstance().RemoveCollider(this);
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
			AssetManager::GetInstance().Render(texture, srcRect, destRect);
		}
	}

	// set visibility of the collision box
	void SetCollisionVisibility(bool visible)
	{
		collisionVisible = visible;
	}

	void OnCollision(CollisionTag _tag)
	{
		switch (tag)
		{
		case CollisionTag::Player:
			entity->GetComponent<PlayerComponent>().OnCollision(_tag);
			break;
		case CollisionTag::Enemy:
			entity->GetComponent<EnemyAIComponent>().OnCollision(_tag);
			break;
		case CollisionTag::PlayerBullet:
			entity->GetComponent<ProjectileComponent>().OnCollision(tag, _tag);
			break;
		case CollisionTag::EnemyBullet:
			entity->GetComponent<ProjectileComponent>().OnCollision(tag, _tag);
			break;
		case CollisionTag::Tile:
			break;
		default:
			break;
		}
	}

private:
	SDL_Texture* texture;
	SDL_Rect destRect;
	SDL_Rect srcRect;
	bool collisionVisible = false;
};