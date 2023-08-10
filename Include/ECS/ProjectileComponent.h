#pragma once
#include "Components.h"

class ProjectileComponent : public Component
{
public:
	int movementDirection = 1;
	ProjectileComponent(int _direction, int _speed)
	{
		movementDirection = _direction;
		speed = _speed;
	}
	~ProjectileComponent()
	{

	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		if (transform->Position.y < 0 || transform->Position.y + transform->Size.y > GameManager::GetInstance().GetResolution().second)
		{
			entity->Destroy();
		}
		else
		{
			transform->Position.y -= movementDirection * speed;
		}
	}

private:
	int speed;
	TransformComponent* transform;
};