#include "ECS.h"

EntityManager EntityManager::instance;
void Entity::AddGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

EntityManager& EntityManager::GetInstance()
{
	return instance;
}
