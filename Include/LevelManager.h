#pragma once
#include <vector>

class LevelManager
{
public: 
	static int GetDifficulty();
	static void SetDifficulty(int _difficulty);

private:
	static int difficulty;
};