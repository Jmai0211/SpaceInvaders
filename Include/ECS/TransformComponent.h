#pragma once
#include "Components.h"
#include "Vector2D.h"
#include <algorithm>

class TransformComponent : public Component
{
public:
	Vector2D Position;
	Vector2D Size;
	float Scale;

	Vector2D Velocity;
	int speed = 7;

	// default constructor
	TransformComponent()
	{
		Position.x = 0.0f;
		Position.y = 0.0f;
		Size.x = 80.0f;
		Size.y = 80.0f;
		Scale = 1.0f;
	}

	// constructor with parameters
	TransformComponent(float x, float y)
	{
		Position.x = x;
		Position.y = y;
		Size.x = 80.0f;
		Size.y = 80.0f;
		Scale = 1.0f;
		Resize();
	}

	void Init() override
	{
		Velocity.x = 0;
		Velocity.y = 0;
	}

	void Update() override
	{
		// Normalize vector for diagonal movement
		if (Velocity.x != 0.0f && Velocity.y != 0.0f)
		{
			float length = std::sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);

			Velocity.x /= length;
			Velocity.y /= length;
		}

		// Update position based on scaled velocity
		Position.x += Velocity.x * speed * Scale;
		Position.y += Velocity.y * speed * Scale;

		// Keep the player in the screen
		if (Position.x < 0)
		{
			Position.x = 0;
		}
		else if (Position.x > GameManager::GetInstance().GetResolution().first - Size.x)
		{
			Position.x = GameManager::GetInstance().GetResolution().first - Size.x;
		}
		if (Position.y < 0)
		{
			Position.y = 0;
		}
		else if (Position.y > GameManager::GetInstance().GetResolution().second - Size.y)
		{
			Position.y = GameManager::GetInstance().GetResolution().second - Size.y;
		}
	}

	// calculate the size and scale of the entity based on the current resolution : reference resolution ratio
	void Resize()
	{
		// Calculate scale based on screen ratio
		std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
		int screenWidth = resolution.first;
		int screenHeight = resolution.second;

		float widthRatio = screenWidth / 1920.0f;
		float heightRatio = screenHeight / 1080.0f;

		Scale = std::min(widthRatio, heightRatio); // Scale the default size

		Size.x = Scale * 80.0f;
		Size.y = Scale * 80.0f;;

		Position.x = Position.x * widthRatio - (Size.x / 2);
		Position.y = Position.y * heightRatio - (Size.y / 2);
	}
};