#pragma once
#include "Components.h"

class ProjectileComponent : public Component
{
public:

	SpriteComponent* mSprite;

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

private:
	TransformComponent* transform;
};