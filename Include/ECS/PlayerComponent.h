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
	}

	void Update() override
	{

	}

	void Input()
	{
		//// Player Y movement, uncomment if need to enable
		//if (InputManager::GetKeyDown(InputManager::Action::UpMovement) && transform->Position.y >= 0)
		//{
		//	transform->Velocity.y = -1;

		//	entity->GetComponent<SpriteComponent>().Play("Walk_Up");
		//}
		//else if (InputManager::GetKeyDown(InputManager::Action::DownMovement) 
		//	&& transform->Position.y <= GameManager::GetInstance().GetResolution().second - transform->Size.y)
		//{
		//	transform->Velocity.y = 1;
		//	entity->GetComponent<SpriteComponent>().Play("Walk_Down");
		//}
		//else
		//{
		//	transform->Velocity.y = 0;
		//}

		// player x movement
		if (InputManager::GetKeyDown(InputManager::Action::LeftMovement) && transform->Position.x >= 0)
		{
			transform->Velocity.x = -1;
			entity->GetComponent<SpriteComponent>().Play("Walk_Left");
		}
		else if (InputManager::GetKeyDown(InputManager::Action::RightMovement)
			&& transform->Position.x <= GameManager::GetInstance().GetResolution().first - transform->Size.x)
		{
			transform->Velocity.x = 1;
			entity->GetComponent<SpriteComponent>().Play("Walk_Right");
		}
		else
		{
			transform->Velocity.x = 0;
		}

		// player shoot function
		if (InputManager::GetKeyDown(InputManager::Action::Shoot) && SDL_GetTicks() - lastFireTime >= 500)
		{
			Game::aManager->CreateProjectile(Vector2D(transform->Position.x + transform->Size.x / 2, transform->Position.y), 1, 5);
			lastFireTime = SDL_GetTicks();
		}
	}

	int GetHealth() const { return health; }
	void SetHealth(int _health) { health = _health; }

private:
	int health;
	Uint32 lastFireTime = 0;
};