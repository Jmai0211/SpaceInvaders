#pragma once
#include "Components.h"

class EnemyAIComponent : public Component
{
public:
	int health = 1;
	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->Velocity.x = movementDirection;

		coolDown = 100;
		
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
	}

	void Input()
	{
		if (coolDown <= 0)
		{
			if (RandomChance(30))
			{
				Game::aManager->CreateProjectile(Vector2D(transform->Position.x + transform->Size.x / 2, transform->Position.y), -1, 5);
			}
			coolDown = rand() % 100 + 100;
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