#pragma once
#include "Components.h"

class EnemyAIComponent : public Component
{
public:
	int health;
	int bulletSpeed;

	EnemyAIComponent(int _health, int _bulletSpeed)
	{
		health = _health;
		bulletSpeed = _bulletSpeed;
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->Velocity.x = movementDirection;

		coolDown = rand() % 100 + 100;
		
		transform->speed = 4;
	}

	void Update() override
	{
		if (transform->Position.x < 0 || transform->Position.x + transform->Size.x > GameManager::GetInstance().GetResolution().first)
		{
			movementDirection *= -1;
			transform->Velocity.x = movementDirection;
		}

		if (coolDown > 0)
		{
			coolDown--;
		}
		else
		{
			Shoot();
		}
	}

	void Shoot()
	{
		if (coolDown <= 0)
		{
			if (RandomChance(30))
			{
				AssetManager::GetInstance().CreateProjectile(Vector2D(transform->Position.x + transform->Size.x / 2, transform->Position.y), -1, bulletSpeed, "EnemyBullet", CollisionTag::EnemyBullet);
			}
			coolDown = rand() % 100 + 100;
		}
	}

	void OnCollision(CollisionTag _tag)
	{
		switch (_tag)
		{
		case CollisionTag::Player:
			break;
		case CollisionTag::PlayerBullet:
			health--;

			if (health <= 0)
			{
				entity->Destroy();

				// update score
				GameManager::GetInstance().SetScore(GameManager::GetInstance().GetScore() + 1);

				TextManager::textArray["Score"]->UpdateText(std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());

				if (GameManager::GetInstance().GetScore() > GameManager::GetInstance().GetHighScore())
				{
					GameManager::GetInstance().SetHighScore(GameManager::GetInstance().GetScore());
					TextManager::textArray["Record"]->UpdateText(std::string(TextManager::GetLocalizedText("Record: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());
				}
			}
			break;
		case CollisionTag::Tile:
			break;
		default:
			break;
		}
	}

private:
	TransformComponent* transform;

	int movementDirection = 1;

	int coolDown = 0;

	// get random chance for shooting
	bool RandomChance(int probability)
	{
		return (rand() % 100) < probability;
	}
};