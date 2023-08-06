#pragma once
#include "SDL.h"

class ColliderComponent;

class CollisionManager
{
public:
	static bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	static bool CheckCollision(const ColliderComponent& object1, const ColliderComponent& object2);
};

