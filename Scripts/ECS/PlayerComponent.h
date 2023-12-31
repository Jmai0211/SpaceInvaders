#pragma once
#include "InputManager.h"
#include "Game.h"

class PlayerComponent : public Component
{
public:
	TransformComponent* transform;

	PlayerComponent(int _health) : health(_health) {};

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->CalculateAdjustedSpeed(6);
	}

	void Update() override
	{
	}

	void VerticalMovement(int axisValue)
	{
		// move up
		if (axisValue < 0)
		{
			if (transform->Position.y < GameManager::GetInstance().GetResolution().second - transform->Size.y)
			{
				transform->Velocity.y = 1;
			}
			else
			{
				transform->Velocity.y = 0;
			}
		}
		// move down
		else if (axisValue > 0)
		{
			if (transform->Position.y > 0)
			{
				transform->Velocity.y = -1;
			}
			else
			{
				transform->Velocity.y = 0;
			}
		}
		// no movement
		else
		{
			transform->Velocity.y = 0;
		}
	}

	void HorizontalMovement(int axisValue)
	{
		// move left
		if (axisValue < 0)
		{
			if (transform->Position.x > 0)
			{
				transform->Velocity.x = -1;
			}
			else
			{
				transform->Velocity.x = 0;
			}
		}
		// move right
		else if (axisValue > 0)
		{
			if (transform->Position.x < GameManager::GetInstance().GetResolution().first - transform->Size.x)
			{
				transform->Velocity.x = 1;
				entity->GetComponent<SpriteComponent>().Play("Walk_Right");
			}
			else
			{
				transform->Velocity.x = 0;
			}
		}
		// no movement
		else
		{
			transform->Velocity.x = 0;
		}
	}

	// Attack event
	void Attack()
	{
		if (SDL_GetTicks() - lastFireTime >= 300)
		{
			AssetManager::GetInstance().CreateProjectile(entity, 1, bulletSpeed, "PlayerBullet", CollisionTag::PlayerBullet);
			lastFireTime = SDL_GetTicks();
		}
	}

	// On collision event
	void OnCollision(CollisionTag _tag)
	{
		switch (_tag)
		{
		case CollisionTag::Enemy:
			break;
		case CollisionTag::EnemyBullet:
			health--;

			TextManager::textArray["Health"]->UpdateText(std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(health)).c_str());

			// game over
			if (health <= 0)
			{
				Game::GameOver();
			}
			break;
		case CollisionTag::Tile:
			break;
		default:
			break;
		}
	}

	int GetHealth() const { return health; }
	void SetHealth(int _health) { health = _health; }

private:
	int health;
	int bulletSpeed = 8;
	Uint32 lastFireTime = 0;
};