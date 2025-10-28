#pragma once

#include <vector>
#include <raylib.h>

#include "settings.h"

struct Bullet
{
	Vector2 position = { 0.0f, 0.0f };
	Vector2 speed = { 0.0f, 0.0f };

	Color color = YELLOW;

	float radius = 5.0f;
	float baseSpeed = 650.0f;

	bool isActive = false;
};

struct Player
{
	Vector2 pos = { 0.0f, 0.0f };
	Vector2 textureOrigin = { 0.0f, 0.0f };
	Vector2 texturePos = { 0.0f, 0.0f };
	Vector2 hitboxPos = { 0.0f, 0.0f };

	Vector2 speed = { 0.0f, 0.0f };

	// Triangle vertices
	Vector2 v1 = { 0.0f, 0.0f };
	Vector2 v2 = { 0.0f, 0.0f };
	Vector2 v3 = { 0.0f, 0.0f };

	Color color = RED;

	Texture texture = { };
	Rectangle textureRec = { };
	Rectangle textureDest = { };

	Bullet bullets[maxAmountOfBullets];
	
	float minAcceleration = 0.002f;
	float maxAcceleration = 1.0f;
	float acceleration = 0.0f;
	float rotation = 0.0f; // in degrees

	float size = 20.0f;
	float height = 0.0f;

	float untouchableTimer = 0.0f;

	int lives = 3;
	int score = 0;
	int hitboxRadius = 10;
	
	bool isActive = false;
};

namespace playerFeatures
{
	void setPlayerDirection(Player& player);
	void drawPlayer(const Player player);
	void movePlayer(Player& player, const float deltaTime);
	void rotatePlayer(Player& player);
	void addScore(Player& player, const int points);
	void setDefault(Player& player);

	bool isAlive(const Player player);
}

namespace playerShooting
{
	void moveBullet(Bullet bullets[], int amountOfBullets, float deltaTime);
	void shootBullet(Player player, Bullet bullets[], int amountOfBullets);
	void drawBullets(Bullet bullets[], int amountOfBullets);
}