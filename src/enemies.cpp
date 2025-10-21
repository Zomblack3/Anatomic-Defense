#include "enemies.h"

#include <iostream>

#include "game.h"

float spawnTimer = 0.0f;

namespace enemiesFeatures
{
	void spawnEnemy(std::vector <Enemy> enemies, float deltaTime)
	{
		int randomEnemyType = 0.0f;

		ENEMY_TYPE enemyType = ENEMY_TYPE::SMALL;

		float randomSpawnPositionX = 0.0f;
		float randomSpawnPositionY = 0.0f;

		// Implementation for spawning an enemy

		if (spawnTimer < 0)
		{
			randomEnemyType = GetRandomValue(1, 3);

			randomSpawnPositionX = static_cast <float>(GetRandomValue(0, settings::screenWidth));

			if (randomSpawnPositionX > 5 || randomSpawnPositionX < settings::screenWidth - 5)
			{
				randomSpawnPositionY = GetRandomValue(0, 100);

				if (randomSpawnPositionY < 50)
					randomSpawnPositionY = 0;
				else
					randomSpawnPositionY = settings::screenHeight;
			}
			else
				randomSpawnPositionY = static_cast <float>(GetRandomValue(0, settings::screenHeight));

			switch (randomEnemyType)
			{
			case 1:

				enemyType = ENEMY_TYPE::SMALL;

				break;
			case 2:

				enemyType = ENEMY_TYPE::MEDIUM;

				break;
			case 3:

				enemyType = ENEMY_TYPE::BIG;

				break;
			default:
				break;
			}

			spawnTimer = 10;
		}
		else if (spawnTimer > 0)
			spawnTimer -= deltaTime;
	}

	void splitEnemy(std::vector<Enemy>& enemies, ENEMY_TYPE type)
	{
		enemies

		//enemies.push_back()
	}

	void moveEnemy(std::vector <Enemy> enemies, float deltaTime)
	{

	}

	void drawEnemy(std::vector <Enemy> enemies)
	{

	}

	Enemy setSplitedEnemy(ENEMY_TYPE type, Vector2 speed, Vector2 position)
	{
		Enemy enemy;

		enemy.isActive = true;

		switch (type)
		{
		case ENEMY_TYPE::MEDIUM:

			enemy.type = ENEMY_TYPE::SMALL;

			break;
		case ENEMY_TYPE::BIG:
			
			enemy.type = ENEMY_TYPE::MEDIUM;
			
			break;
		default:

			break;
		}

		enemy.speed.x = GetRandomValue(0, speed.x);
		enemy.speed.y = GetRandomValue(0, speed.y);

		enemy.position = position;

		return enemy;
	}
}
