#pragma once
#include "SDL.h"

class ColliderComponent;
class Game;

class CollisionManager
{
public:
	// function to check box collision
	static bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	// function to take two colliders and check box collision
	static bool CheckCollision(const ColliderComponent& object1, const ColliderComponent& object2);

	// function to check all collisions
	static void Update();

private:
	static Game* game;
};

