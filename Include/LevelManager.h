#pragma once
#include <vector>

class LevelManager
{
public: 

	static void Update();

	static void Render();

	static void Clean();

	static int GetDifficulty();
	static void SetDifficulty(int _difficulty);

private:
	static int difficulty;
};