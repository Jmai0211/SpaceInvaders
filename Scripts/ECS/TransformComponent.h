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

	void CalculateAdjustedSpeed(int _originalSpeed)
	{
		// Define your reference screen resolution
		const float referenceScreenWidth = 1920.0f;
		const float referenceScreenHeight = 1080.0f;

		// Calculate the scaling factors for width and height
		float widthScale = static_cast<float>(GameManager::GetInstance().GetResolution().first) / referenceScreenWidth;
		float heightScale = static_cast<float>(GameManager::GetInstance().GetResolution().second) / referenceScreenHeight;

		// Choose the smaller scaling factor to maintain aspect ratio
		float scale = std::min(widthScale, heightScale);

		// Calculate the adjusted speed
		speed = static_cast<int>(_originalSpeed * scale);
	}

private:
	static const int ReferenceScreenWidth = 1920;
	static const int ReferenceScreenHeight = 1080;

	void Rescale()
	{
		// Calculate scale based on screen ratio
		int screenWidth = GameManager::GetInstance().GetResolution().first;
		int screenHeight = GameManager::GetInstance().GetResolution().second;

		float widthScale = static_cast<float>(screenWidth) / ReferenceScreenWidth;
		float heightScale = static_cast<float>(screenHeight) / ReferenceScreenHeight;

		// Calculate new size based on scale
		float newWidth = defaultSize.x * widthScale;
		float newHeight = defaultSize.y * heightScale;

		Size.x = static_cast<int>(std::round(newWidth));
		Size.y = static_cast<int>(std::round(newHeight));
	}

	void Reposition()
	{
		// Calculate scale based on screen ratio
		int screenWidth = GameManager::GetInstance().GetResolution().first;
		int screenHeight = GameManager::GetInstance().GetResolution().second;

		float widthScale = static_cast<float>(screenWidth) / ReferenceScreenWidth;
		float heightScale = static_cast<float>(screenHeight) / ReferenceScreenHeight;

		// Calculate position based on the new size
		int referenceX = static_cast<int>((Position.x) * widthScale);
		int referenceY = static_cast<int>((Position.y) * heightScale);

		Position.x = referenceX;
		Position.y = referenceY;
	}
};