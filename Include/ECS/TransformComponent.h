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
		Position.x += Velocity.x * speed;
		Position.y += Velocity.y * speed;

		// Round the position to the nearest integer
		Position.x = std::round(Position.x);
		Position.y = std::round(Position.y);
	}

	void Resize()
	{
		// Calculate scale based on screen ratio
		std::pair<int, int> resolution = GameManager::GetInstance().GetResolution();
		float screenWidth = static_cast<float>(resolution.first);
		float screenHeight = static_cast<float>(resolution.second);

		float widthRatio = screenWidth / 1920.0f;
		float heightRatio = screenHeight / 1080.0f;

		// sprites with perfect squares
		if (defaultSize.x == defaultSize.y)
		{
			float scale = std::min(widthRatio, heightRatio);
			Size.x = defaultSize.x * scale;
			Size.y = defaultSize.y * scale;
			Position.x = std::floor(Position.x * scale - (Size.x / 2.0f));
			Position.y = std::floor(Position.y * scale - (Size.y / 2.0f));
		}
		else
		{
			// For non-square sprites, use the width and height ratios separately
			Size.x = std::round(defaultSize.x * widthRatio);
			Size.y = std::round(defaultSize.y * heightRatio);
			Position.x = std::floor(Position.x * widthRatio - (Size.x / 2.0f));
			Position.y = std::floor(Position.y * heightRatio - (Size.y / 2.0f));
		}
	}

	double roundToDecimalPlaces(double value, int decimalPlaces) {
		double factor = std::pow(10, decimalPlaces);
		return std::round(value * factor) / factor;
	}
};