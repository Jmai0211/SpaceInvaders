#include "LevelManager.h"
#include "ECS.h"
#include "Components.h"

LevelManager& LevelManager::GetInstance()
{
	static LevelManager instance;
	return instance;
}

int LevelManager::GetDifficulty()
{
	return difficulty;
}

void LevelManager::SetDifficulty(int _difficulty)
{
	difficulty = _difficulty;
}

void LevelManager::SpawnEnemy()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			// Create a new enemy entity and store a reference to it in the vector
			Entity& enemy = EntityManager::GetInstance().AddEntity("Alien");

			// Add a TransformComponent to the enemy entity
			enemy.AddComponent<TransformComponent>(100 + x * 120, 200 + y * 120, 80, 80);

			enemy.AddComponent<SpriteComponent>("Enemy");

			enemy.AddComponent<ColliderComponent>(CollisionTag::Enemy);

			enemy.AddComponent<EnemyAIComponent>(1 + static_cast<int>(LevelManager::GetDifficulty() / 5), 3 + LevelManager::GetDifficulty());

			enemy.SetDestroyEnemyCallback([this](Entity* enemy) {
				CheckEnemySpawn();
				});

			enemy.AddGroup(Enemy);
		}
	}
}

void LevelManager::CheckEnemySpawn()
{
	std::vector<Entity*> temp = EntityManager::GetInstance().FindEntitiesWithSubstring("Alien");
	if (temp.empty() && GameManager::GetInstance().GetState() == GameState::Playing)
	{
		SetDifficulty(GetDifficulty() + 1);
		SpawnEnemy();
	}
}
