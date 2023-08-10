#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;
	int spacing = 0;
	Vector2D animationStart;

	Animation() = default;
	Animation(int _index, int srcX, int srcY, int _frames, int _spacing, int _speed)
	{
		index = _index;
		animationStart.x = srcX;
		animationStart.y = srcY;
		frames = _frames;
		spacing = _spacing;
		speed = _speed;
	}
};