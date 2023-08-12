#pragma once
#include "Components.h"
#include "Vector2D.h"
#include <algorithm>
#include "GameManager.h"
#include <cmath>

class TransformComponent : public Component
{
public:
	Vector2D Position;
	Vector2D Size;
	int Scale;

	Vector2D defaultSize;

	Vector2D Velocity;
	int speed = 5;

	// default constructor
	TransformComponent()
	{
		Position.Zero();
		Size.Zero();
		Scale = 1;
	}

	// constructor with parameters
	TransformComponent(int x, int y, int w, int h, bool resize = true)
	{
		Position.x = x;
		Position.y = y;
		Size.x = w;
		Size.y = h;
		defaultSize.x = w;
		defaultSize.y = h;
		Scale = 1;

		Rescale();

		if (resize)
		{
			Reposition();
		}
		else
		{
			// set pivot point to center
			Position.x = static_cast<int>(Position.x - (Size.x / 2.0f));
			Position.y = static_cast<int>(Position.y - (Size.y / 2.0f));
		}
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
			int length = static_cast<int>(std::sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y));
			Velocity.x /= length;
			Velocity.y /= length;
		}

		// Update position based on scaled velocity
		Position.x += Velocity.x * speed;
		Position.y += Velocity.y * speed;
	}

	void Rescale()
	{
		// Calculate scale based on screen ratio
		std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
		int screenWidth = resolution.first;
		int screenHeight = resolution.second;

		float widthRatio = static_cast<float>(screenWidth) / 1920.0f;
		float heightRatio = static_cast<float>(screenHeight) / 1080.0f;

		// sprites with perfect squares
		if (defaultSize.x == defaultSize.y)
		{
			float scale = std::min(widthRatio, heightRatio);
			Size.x = static_cast<int>(std::round(defaultSize.x * scale));
			Size.y = static_cast<int>(std::round(defaultSize.y * scale));
		}
		else
		{
			// For non-square sprites, use the width and height ratios separately
			Size.x = static_cast<int>(std::round(defaultSize.x * widthRatio));
			Size.y = static_cast<int>(std::round(defaultSize.y * heightRatio));
		}
	}

	void Reposition()
	{
		// Calculate scale based on screen ratio
		std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
		int screenWidth = resolution.first;
		int screenHeight = resolution.second;

		float widthRatio = static_cast<float>(screenWidth) / 1920.0f;
		float heightRatio = static_cast<float>(screenHeight) / 1080.0f;

		Position.x = static_cast<int>(std::round(Position.x * widthRatio - (Size.x / 2.0f)));
		Position.y = static_cast<int>(std::round(Position.y * heightRatio - (Size.y / 2.0f)));
	}
};