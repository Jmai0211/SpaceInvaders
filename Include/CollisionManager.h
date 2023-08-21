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

	void AddCollider(ColliderComponent* entity);
	void RemoveCollider(ColliderComponent* entity);

	// function to check box collision
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	// function to take two colliders and check box collision
	bool CheckCollision(ColliderComponent* object1, ColliderComponent* object2);

	// function to check all collisions
	void Update();

private:
	CollisionManager() {
		// Private constructor to prevent direct instantiation
		// Initialization code here
	}

	CollisionManager(const CollisionManager&) = delete; // Disable copy constructor
	CollisionManager& operator=(const CollisionManager&) = delete; // Disable assignment operator
	Game* game;

	std::vector<ColliderComponent*> registeredEntities;
};

