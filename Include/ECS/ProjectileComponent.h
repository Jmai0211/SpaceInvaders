#pragma once
#include "Components.h"
#include "ColliderComponent.h"

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

	void OnCollision(CollisionTag _tag, CollisionTag _otherTag)
	{
		switch (_otherTag)
		{
		case CollisionTag::Player:
			if (_tag == CollisionTag::EnemyBullet)
			{
				entity->Destroy();
			}
			break;
		case CollisionTag::Enemy:
			if (_tag == CollisionTag::PlayerBullet)
			{
				entity->Destroy();
			}
			break;
		default:
			break;
		}
	}

private:
	int speed;
	TransformComponent* transform;
};