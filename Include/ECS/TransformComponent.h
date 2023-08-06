#pragma once
#include "Components.h"
#include "Vector2D.h"
#include <algorithm>
#include "GameManager.h"

class TransformComponent : public Component
{
public:
	Vector2D Position;
	Vector2D Size;
	float Scale;

	Vector2D defaultSize;

	Vector2D Velocity;
	float speed = 7.0f;

	// default constructor
	TransformComponent()
	{
		Position.Zero();
		Size.Zero();
		Scale = 1.0f;
	}

	// constructor with parameters
	TransformComponent(float x, float y, float w, float h)
	{
		Position.x = x;
		Position.y = y;
		Size.x = w;
		Size.y = h;
		defaultSize.x = w;
		defaultSize.y = h;
		Scale = 1.0f;
		Resize();
	}

	void Init() override
	{
		Velocity.Zero();
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
		Position.x += Velocity.x * speed * (Size.x / defaultSize.x);
		Position.y += Velocity.y * speed * (Size.y / defaultSize.y);

		// Round the position to the nearest integer
		Position.x = round(Position.x);
		Position.y = round(Position.y);
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

		float scale = std::min(widthRatio, heightRatio);

		Size.x = round(defaultSize.x * scale);
		Size.y = round(defaultSize.y * scale);

		Position.x = round(Position.x * scale - (Size.x / 2.0f));
		Position.y = round(Position.y * scale - (Size.y / 2.0f));
	}
};