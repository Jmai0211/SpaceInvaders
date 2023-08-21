#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "ECS.h"
#include "Game.h"

CollisionManager& CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return instance;
}

void CollisionManager::AddCollider(ColliderComponent* entity)
{
	registeredEntities.push_back(entity);
}

void CollisionManager::RemoveCollider(ColliderComponent* entity)
{
	auto it = std::find(registeredEntities.begin(), registeredEntities.end(), entity);
	if (it != registeredEntities.end())
	{
		registeredEntities.erase(it);
	}
}

bool CollisionManager::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	return object1.x <= object2.x + object2.w && 
		   object2.x <= object1.x + object1.w &&
		   object1.y <= object2.y + object2.h && 
		   object2.y <= object1.y + object1.h;
}

bool CollisionManager::CheckCollision(ColliderComponent* object1, ColliderComponent* object2)
{
	if (CheckCollision(object1->collider, object2->collider))
	{
		//std::cout << object1.tag << " hit " << object2.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void CollisionManager::Update()
{
	for (auto collider1 : registeredEntities)
	{
		for (auto collider2 : registeredEntities)
		{
			if (collider1->entity->IsActive() && collider2->entity->IsActive() && collider1 != collider2)
			{
				if (CheckCollision(collider1, collider2))
				{
					collider1->OnCollision(collider2->tag);
					collider2->OnCollision(collider1->tag);
				}
			}
		}
	}
}
