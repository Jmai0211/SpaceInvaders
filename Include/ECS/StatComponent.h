#pragma once
#include "Components.h"

class StatComponent : public Component
{
public:
	StatComponent()
	{
		health = 1;
		movementSpeed = 5;
	}

	StatComponent(int _health, int _speed)
	{
		health = _health;
		movementSpeed = _speed;
	}

	int Health() const { return health; }
	void SetHealth(int _health) { health = _health; }

	int Speed() const { return movementSpeed; }
	void SetSpeed(int _speed) { movementSpeed = _speed; }

private:
	int health;
	int movementSpeed;
};