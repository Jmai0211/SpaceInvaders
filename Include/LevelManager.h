#pragma once
#include <vector>

class LevelManager
{
public: 
	static void Update();

	static void Render();

	static void Clean();

private:
	int difficulty = -1;
};