#include "LevelManager.h"

int LevelManager::difficulty = 1;

void LevelManager::Update()
{
}

// render all level related data
void LevelManager::Render()
{

}

// delete all level related data
void LevelManager::Clean()
{

}

int LevelManager::GetDifficulty()
{
	return difficulty;
}

void LevelManager::SetDifficulty(int _difficulty)
{
	difficulty = _difficulty;
}
