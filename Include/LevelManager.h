#pragma once
#include <vector>

class LevelManager
{
public: 
	static LevelManager& GetInstance();

	// Return current game difficulty
	int GetDifficulty();
	// Set current game difficulty
	void SetDifficulty(int _difficulty);

	// Spawn Enemies
	void SpawnEnemy();

private:
	LevelManager() = default;
	~LevelManager() = default;
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;

	int difficulty = 0;
	// Check if new set of enemies should be spawned
	void CheckEnemySpawn();
};