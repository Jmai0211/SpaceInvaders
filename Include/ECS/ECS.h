#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>
#include <functional>
#include "GameManager.h"
#include <map>
#include <string>

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
		if (destroyCallback)
		{
			destroyCallback(this);
		}
	}

	void SetDestroyCallback(std::function<void(Entity*)> callback)
	{
		destroyCallback = callback;
	}

	void Update()
	{
		for (auto& c : components) c->Update();
	}

	void Render()
	{
		for (auto& c : components) c->Render();
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

	std::function<void(Entity*)> destroyCallback;
};

class EntityManager
{
public:
	static EntityManager& GetInstance() 
	{
		static EntityManager instance;
		return instance;
	}

	void Update()
	{
		for (auto& e : entityArray) e.second->Update();
	}

	void Render()
	{
		for (auto& e : entityArray) e.second->Render();
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
		for (auto it = entityArray.begin(); it != entityArray.end(); )
		{
			if (!it->second->IsActive())
			{
				// Erase the entity from the map and move the iterator to the next element
				it = entityArray.erase(it);

			}
			else
			{
				// Move to the next element in the map
				++it;
			}
		}
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*> GetGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& AddEntity(std::string baseName) 
	{
		std::string uniqueName = baseName;
		int number = 1;

		// Keep incrementing the number until a unique name is found
		while (entityArray.find(uniqueName) != entityArray.end()) 
		{
			uniqueName = baseName + std::to_string(number);
			number++;
		}

		// Create the entity and add it to the map
		entityArray.emplace(uniqueName, std::make_unique<Entity>());

		return *entityArray[uniqueName];
	}

	// Function to find an entity by name
	Entity* FindEntity(std::string entityName) 
	{
		auto it = entityArray.find(entityName);
		if (it != entityArray.end()) {
			return it->second.get();
		}
		return nullptr; // Entity not found
	}

	// Function to find all entities with names containing a certain substring
	std::vector<Entity*> FindEntitiesWithSubstring(std::string substring) 
	{
		std::vector<Entity*> result;

		for (const auto& pair : entityArray) 
		{
			if (pair.first.find(substring) != std::string::npos) 
			{
				result.push_back(pair.second.get());
			}
		}

		return result;
	}

	// Function to find all entities with a specified component
	template <typename T>
	std::vector<Entity*> FindEntitiesWithComponent() 
	{
		std::vector<Entity*> result;

		for (const auto& pair : entityArray) 
		{
			if (pair.second->hasComponent<T>()) 
			{
				result.push_back(pair.second.get());
			}
		}

		return result;
	}

	std::string GetEntityID(Entity* entity)
	{
		for (const auto& pair : entityArray)
		{
			if (pair.second.get() == entity)
			{
				return pair.first;
			}
		}

		// If not found, return an empty string or handle the error as needed
		return "";
	}

private:
	EntityManager() {
		// Private constructor to prevent direct instantiation
		// Initialization code here
	}

	EntityManager(const EntityManager&) = delete; // Disable copy constructor
	EntityManager& operator=(const EntityManager&) = delete; // Disable assignment operator

	std::map<std::string, std::unique_ptr<Entity>> entityArray;

	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

	std::function<void(Entity*)> destroyEnemyCallback;
};