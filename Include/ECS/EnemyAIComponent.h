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
	}

	void Update() override
	{
		if (transform->Position.x < 0 || transform->Position.x + transform->Size.x > GameManager::GetInstance().GetResolution().first)
		{
			movementDirection *= -1;
			transform->Velocity.x = movementDirection;
		}
	}

private:
	TransformComponent* transform;

	int movementDirection = 1;

	// get random chance for shooting
	bool RandomChance(int probability)
	{
		return (rand() % 100) < probability;
	}
};