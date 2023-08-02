#include "Player.h"

Player::Player(const char* textureSheet, const char* bulletTextureSheet, int x, int y, int _health) : GameObject(textureSheet, bulletTextureSheet, x, y)
{
	bulletDirection = -1;
	health = _health;
}

Player::~Player()
{

}

// handle player input
void Player::Input()
{
	// move left
	if (InputManager::GetKeyDown(InputManager::Action::LeftMovement) && destRect.x >= 0)
	{
		movementDirection = -1;
		Move();
	}
	// move right
	else if (InputManager::GetKeyDown(InputManager::Action::RightMovement) && destRect.x + destRect.w <= GameManager::GetInstance().GetResolution().first)
	{
		movementDirection = 1;
		Move();
	}

	// shoot
	if (InputManager::GetKeyDown(InputManager::Action::Shoot) && !isShotActive)
	{
		Shoot();
	}
}

void Player::Update()
{
	GameObject::Update();
}
