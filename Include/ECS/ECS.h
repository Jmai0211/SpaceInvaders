#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>
#include <functional>
#include "GameManager.h"

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual ~Component() {};
};

class Entity
{
public:
	Entity() 
	{
		// Initialize componentArray with nullptr values
		for (std::size_t i = 0; i < maxComponents; ++i)
		{
			componentArray[i] = nullptr;
		}
	}

	~Entity()
	{
		if (destroyEnemyCallback)
		{
			destroyEnemyCallback(this);
		}
	}

	void Update()
	{
		for (auto& c : components) c->Update();
	}

	void Render()
	{
		for (auto& c : components) c->Render();
	}

	// call back used to remove enemy pointer from game.h when the enemy is destroyed
	void SetDestroyEnemyCallback(std::function<void(Entity*)> callback)
	{
		destroyEnemyCallback = callback;
	}

	bool IsActive() const { return active; }

	void Destroy() { active = false; }

	bool HasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void AddGroup(Group mGroup);
	void RemoveGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	// add component to the entity
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	// return the desired component from the entity
	template <typename T> T& GetComponent() const
	{
		// find the component in the map
		auto target(componentArray[GetComponentTypeID<T>()]);
		// if target found, return component, else return null pointer
		return *static_cast<T*>(target);
	}

private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

	std::function<void(Entity*)> destroyEnemyCallback;
};

class EntityManager
{
public:
	static EntityManager& GetInstance() {
		static EntityManager instance;
		return instance;
	}

	void Update()
	{
		for (auto& e : entityArray) e->Update();
	}

	void Render()
	{
		for (auto& e : entityArray) e->Render();
	}

	void Refresh()
	{
		// if the return is not active or if the entity doesn't have the group, remove it
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
				{
					return !mEntity->IsActive() || !mEntity->HasGroup(i);
				}),
				std::end(v));
		}

		// if the entity is not active, remove it
		entityArray.erase(std::remove_if(std::begin(entityArray), std::end(entityArray),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(entityArray));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*> GetGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entityArray.emplace_back(std::move(uPtr));

		return *e;
	}

	// Function to queue entity additions
	// use this for creating entities in update
	void QueueEntityToAdd(std::function<void()> createFunction)
	{
		if (GameManager::GetInstance().GetActiveGame())
		{
			entitiesToAddQueue.push_back(createFunction);
		}
	}

	// Process the entity addition queue
	void ProcessEntityAdditions()
	{
		for (auto& createFunction : entitiesToAddQueue)
		{
			createFunction();
		}
		entitiesToAddQueue.clear();
	}

private:
	EntityManager() {
		// Private constructor to prevent direct instantiation
		// Initialization code here
	}

	EntityManager(const EntityManager&) = delete; // Disable copy constructor
	EntityManager& operator=(const EntityManager&) = delete; // Disable assignment operator

	std::vector<std::unique_ptr<Entity>> entityArray;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

	std::vector<std::function<void()>> entitiesToAddQueue;
};