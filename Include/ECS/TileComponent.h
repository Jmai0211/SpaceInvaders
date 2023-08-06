#pragma once
#include "ECS.h"
#include "Components.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		// add more sprites as needed and assign it to one integer value
		case 0:
			path = "Assets/CollisionBox.png";
			break;
		case 121:
			path = "Assets/Overworld-121.png";
			break;
		case 122:
			path = "Assets/Overworld-122.png";
			break;
		case 123:
			path = "Assets/Overworld-123.png";
			break;
		case 161:
			path = "Assets/Overworld-161.png";
			break;
		case 162:
			path = "Assets/Overworld-162.png";
			break;
		case 163:
			path = "Assets/Overworld-163.png";
			break;
		case 201:
			path = "Assets/Overworld-201.png";
			break;
		case 202:
			path = "Assets/Overworld-202.png";
			break;
		case 203:
			path = "Assets/Overworld-203.png";
			break;
		default:
			break;
		}
	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.w);
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->GetComponent<SpriteComponent>();
	}
};