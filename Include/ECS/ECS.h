#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>

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
	Entity(EntityManager& mManager) : manager(mManager) {}

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
	EntityManager& manager;

	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};

class EntityManager
{
public:
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
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entityArray.emplace_back(std::move(uPtr));

		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entityArray;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};