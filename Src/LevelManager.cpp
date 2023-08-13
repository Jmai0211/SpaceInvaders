#include "LevelManager.h"

int LevelManager::difficulty = 1;

int LevelManager::GetDifficulty()
{
	return difficulty;
}

void LevelManager::SetDifficulty(int _difficulty)
{
	difficulty = _difficulty;
}
