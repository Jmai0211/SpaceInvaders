#include "ECS.h"

void Entity::AddGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	EntityManager::GetInstance().AddToGroup(this, mGroup);
}
