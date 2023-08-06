#pragma once
#include "Components.h"
#include "InputManager.h"

class PlayerInputComponent : public Component
{
public:
	TransformComponent* transform;

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		// Player Y movement, uncomment if need to enable
		//if (InputManager::GetKeyDown(InputManager::Action::UpMovement) && transform->Position.y >= 0)
		//{
		//	transform->Velocity.y = -1;
		//}
		//else if (InputManager::GetKeyDown(InputManager::Action::DownMovement) 
		//	&& transform->Position.y <= GameManager::GetInstance().GetResolution().second - transform->Size.y)
		//{
		//	transform->Velocity.y = 1;
		//}
		//else
		//{
		//	transform->Velocity.y = 0;
		//}

		// player x movement
		if (InputManager::GetKeyDown(InputManager::Action::LeftMovement) && transform->Position.x >= 0)
		{
			transform->Velocity.x = -1;
		}
		else if (InputManager::GetKeyDown(InputManager::Action::RightMovement) 
			&& transform->Position.x <= GameManager::GetInstance().GetResolution().first - transform->Size.x)
		{
			transform->Velocity.x = 1;
		}
		else
		{
			transform->Velocity.x = 0;
		}

		if (InputManager::GetKeyDown(InputManager::Action::Shoot) && SDL_GetTicks() - lastFireTime >= 200)
		{
			lastFireTime = SDL_GetTicks();
		}
	}
private:
	Uint32 lastFireTime = 0;
};