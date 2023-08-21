#pragma once
#include <vector>

class LevelManager
{
public: 
	static LevelManager& GetInstance();
	int GetDifficulty();
	void SetDifficulty(int _difficulty);

	void SpawnEnemy();

private:
	LevelManager() = default;
	~LevelManager() = default;
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;

	int difficulty = 0;
	void CheckEnemySpawn();
};