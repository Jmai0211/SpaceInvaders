#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"
#include "Game.h"

class SpriteComponent : public Component
{
public:
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SpriteComponent() = default;

	SpriteComponent(std::string id)
	{
		SetTexture(id);
		srcRect.x = 0;
		srcRect.y = 0;
	}

	SpriteComponent(std::string id, SDL_Rect _srcRect)
	{
		SetTexture(id);
		srcRect = _srcRect;
	}

	// srcX and src Y are the starting position of the texture in a sprite sheet
	// if your character starts at (0,0), pass in 0 for both srcX and srcY
	// spacing represents the spacing between each animation frame
	// if there are no spacing between each one, you can leave it as 0
	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation walkDown = Animation(0, 4, 25, 4, 4, 200);
		Animation walkRight = Animation(0, 8, 151, 4, 4, 200);

		Animation walkUp = Animation(0, 0, 275, 4, 4, 200);

		Animation walkLeft = Animation(0, 4, 407, 4, 4, 200);
		animations.emplace("Walk_Down", walkDown);
		animations.emplace("Walk_Right", walkRight);
		animations.emplace("Walk_Up", walkUp);
		animations.emplace("Walk_Left", walkLeft);

		Play("Walk_Right");
		SetTexture(id);
	}

	void SetTexture(std::string id)
	{
		texture = Game::aManager->GetTexture(id);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.w = static_cast<int>(transform->defaultSize.x);
		srcRect.h = static_cast<int>(transform->defaultSize.y);
	}

	void Update() override
	{
		if (animated)
		{
			srcRect.x = static_cast<int>((srcRect.w + spacing) * ((SDL_GetTicks() / speed) % frames));
			srcRect.y = animIndex * transform->Size.y + animationStart.y;
		}	

		destRect.x = transform->Position.x;
		destRect.y = transform->Position.y;
		destRect.w = transform->Size.x;
		destRect.h = transform->Size.y;
	}

	void Render() override
	{
		TextureManager::Render(texture, srcRect, destRect);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		animationStart = animations[animName].animationStart;
		spacing = animations[animName].spacing;
		speed = animations[animName].speed;
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	Vector2D animationStart;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	int spacing = 0;
};