#include "CollisionManager.h"
#include "ColliderComponent.h"

bool CollisionManager::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	return object1.x <= object2.x + object2.w && 
		   object2.x <= object1.x + object1.w &&
		   object1.y <= object2.y + object2.h && 
		   object2.y <= object1.y + object1.h;
}

bool CollisionManager::CheckCollision(const ColliderComponent& object1, const ColliderComponent& object2)
{
	// ignores collision with self
	if (&object1 != &object2)
	{
		if (CheckCollision(object1.collider, object2.collider))
		{
			//std::cout << object1.tag << " hit " << object2.tag << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
