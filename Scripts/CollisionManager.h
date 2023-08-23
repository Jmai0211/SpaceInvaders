#pragma once
#include "SDL.h"
#include <vector>

class ColliderComponent;
class Entity;
class Game;

class CollisionManager
{
public:
	static CollisionManager& GetInstance();

	// Add the collider to the vector when the collider first created
	void AddCollider(ColliderComponent* entity);

	// Remove the colllider from the vector when the collider is destroyed
	void RemoveCollider(ColliderComponent* entity);

	// Check box collision
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	// Take two colliders and check box collision
	bool CheckCollision(ColliderComponent* object1, ColliderComponent* object2);

	// Check all collisions
	void Update();

private:
	CollisionManager() 
	{
		// Private constructor to prevent direct instantiation
		// Initialization code here
	}

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	Game* game;

	std::vector<ColliderComponent*> registeredEntities;
};

