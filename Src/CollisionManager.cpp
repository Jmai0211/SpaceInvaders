#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "ECS.h"
#include "Game.h"

Game* CollisionManager::game;

bool CollisionManager::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	return object1.x <= object2.x + object2.w && 
		   object2.x <= object1.x + object1.w &&
		   object1.y <= object2.y + object2.h && 
		   object2.y <= object1.y + object1.h;
}

bool CollisionManager::CheckCollision(const ColliderComponent& object1, const ColliderComponent& object2)
{
	// ignores collision with self
	if (&object1 != &object2)
	{
		if (CheckCollision(object1.collider, object2.collider))
		{
			//std::cout << object1.tag << " hit " << object2.tag << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void CollisionManager::Update()
{
	std::vector<Entity*> temp = game->eManager.FindEntitiesWithSubstring("");
	Entity* player = game->eManager.FindEntity("Player");

	// check for all collisions against the player
	for (auto c : temp)
	{
		// enemy bullet
		if (c->hasComponent<ColliderComponent>())
		{
			auto& collider = c->GetComponent<ColliderComponent>();
			if (!collider.destroyed &&
				CollisionManager::CheckCollision(player->GetComponent<ColliderComponent>(), collider) &&
				collider.tag == "Projectile" &&
				collider.entity->GetComponent<ProjectileComponent>().movementDirection < 0)
			{
				player->GetComponent<PlayerComponent>().SetHealth(player->GetComponent<PlayerComponent>().GetHealth() - 1);

				TextManager::textArray["Health"]->UpdateText(std::string(TextManager::GetLocalizedText("Health: ")).append(std::to_string(player->GetComponent<PlayerComponent>().GetHealth())).c_str());

				collider.destroyed = true;

				collider.entity->Destroy();

				if (player->GetComponent<PlayerComponent>().GetHealth() <= 0)
				{
					game->GameOver();
				}

			}
		}

		// check for all collisions against the enemies
		for (size_t i = 0; i < temp.size(); i++)
		{
			auto e = temp[i];
			if (e->hasComponent<EnemyAIComponent>())
			{
				for (size_t j = i + 1; j < temp.size(); j++)
				{
					auto& collider = c->GetComponent<ColliderComponent>();

					// player bullet
					if (!collider.destroyed &&
						CollisionManager::CheckCollision(temp[i]->GetComponent<ColliderComponent>(), collider) &&
						collider.tag == "Projectile" &&
						collider.entity->GetComponent<ProjectileComponent>().movementDirection > 0)
					{
						collider.destroyed = true; // Mark the bullet as used

						collider.entity->Destroy();

						e->GetComponent<EnemyAIComponent>().health--;
						if (e->GetComponent<EnemyAIComponent>().health <= 0)
						{
							e->Destroy();
							// update score
							GameManager::GetInstance().SetScore(GameManager::GetInstance().GetScore() + 1);
							TextManager::textArray["Score"]->UpdateText(std::string(TextManager::GetLocalizedText("Score: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());

							if (GameManager::GetInstance().GetScore() > GameManager::GetInstance().GetHighScore())
							{
								GameManager::GetInstance().SetHighScore(GameManager::GetInstance().GetScore());
								TextManager::textArray["Record"]->UpdateText(std::string(TextManager::GetLocalizedText("Record: ")).append(std::to_string(GameManager::GetInstance().GetScore())).c_str());
							}
						}
					}
				}
			}
		}
	}
}
