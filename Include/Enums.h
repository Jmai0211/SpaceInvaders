#ifndef ENUMS_H
#define ENUMS_H

enum class CollisionTag
{
	Player,
	Enemy,
	PlayerBullet,
	EnemyBullet,
	Tile,
};

enum class GameState
{
	Menu,
	Option,
	Playing,
	GameOver
};

enum class Language
{
	English,
	Chinese
};

enum RenderLayer : std::size_t
{
	Tile,
	Enemy,
	Player,
	Projectile,
};

// Add other enums here
#endif