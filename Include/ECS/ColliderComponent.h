#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	void Init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();
	}

	
};