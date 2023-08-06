#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
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
	void Update()
	{
		for (auto& c : components) c->Update();
	}

	void Render()
	{
		for (auto& c : components) c->Render();
	}

	bool isActive() const { return active; }

	void Destroy() { active = false; }

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
		entityArray.erase(std::remove_if(std::begin(entityArray), std::end(entityArray),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entityArray));
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entityArray.emplace_back(std::move(uPtr));

		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entityArray;
};