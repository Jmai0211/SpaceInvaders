#pragma once
#include "Components.h"

class EnemyAIComponent : public Component
{
public:
	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->Velocity.x = movementDirection;
	}

	void Update() override
	{
		if (transform->Position.x < 0 || transform->Position.x + transform->Size.x >= GameManager::GetInstance().GetResolution().first)
		{
			movementDirection *= -1.0f;
			transform->Velocity.x = movementDirection;
		}
	}

private:
	TransformComponent* transform;

	float movementDirection = 1.0f;

	// get random chance for shooting
	bool RandomChance(int probability)
	{
		return (rand() % 100) < probability;
	}
};