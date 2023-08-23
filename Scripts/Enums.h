#pragma once
#ifndef ENUMS_H
#define ENUMS_H

// Enum for the collider tag
enum class CollisionTag
{
	Player,
	Enemy,
	PlayerBullet,
	EnemyBullet,
	Tile,
};

// Enum for the current state of the game
enum class GameState
{
	Menu,
	Option,
	Playing,
	GameOver
};

// Enum for supported languages
enum class Language
{
	English,
	Chinese
};

// Enum for render layers in which the entities are rendered
enum RenderLayer : std::size_t
{
	Tile,
	Enemy,
	Player,
	Projectile,
};

// Enum for all input actions
enum class Action
{
	LeftMovement,
	RightMovement,
	UpMovement,
	DownMovement,
	Left,
	Right,
	Up,
	Down,
	Shoot,
	Confirm,
	Back,
};

// Enum for control type
enum class Control
{
	Keyboard,
	Controller
};

// Add other enums here
#endif