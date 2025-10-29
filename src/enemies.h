#pragma once

#include <vector>
#include <raylib.h>

#include "player.h"

enum class ENEMY_TYPE
{
	SMALL,
	MEDIUM,
	BIG
};

struct Enemy
{
	Vector2 position = { 0.0f, 0.0f };
	Vector2 speed = { 0.0f, 0.0f };

	Color color = GREEN;

	Texture texture = { };

	ENEMY_TYPE type = ENEMY_TYPE::SMALL;

	int amountOfInternalEnemies = 0;
	int points = 0;

	float radius = 0.0f;
	float baseSpeed = 0.0f;
	float rotation = 0.0f;

	bool isActive = false;
};

namespace enemiesFeatures
{
	void spawnEnemy(std::vector <Enemy>& enemies, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, float deltaTime);
	void splitEnemy(std::vector <Enemy>& enemies, Enemy enemySplited, ENEMY_TYPE type, int index, Texture smallEnemy, Texture mediumEnemy);
	void moveEnemy(std::vector <Enemy>& enemies, float deltaTime);
	void drawEnemy(std::vector <Enemy> enemies);

	void checkBulletEnemyCollition(std::vector <Enemy>& enemies, Player& player, Texture smallEnemy, Texture mediumEnemy);
	void checkPlayerEnemyCollition(std::vector <Enemy>& enemies, Player& player, float deltaTime, Texture smallEnemy, Texture mediumEnemy);

	Enemy setSplitedEnemy(ENEMY_TYPE type, Vector2 position, Texture smallEnemy, Texture mediumEnemy);
}



