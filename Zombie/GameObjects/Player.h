#pragma once
#include "SpriteGo.h"

class SceneGame;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.f, 0.f };
	float speed = 500.f;

	SceneGame* sceneGame = nullptr;

	bool isFiring = false;
	float fireInterval = 0.5f;
	float fireTimer = 0.f;
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;

public:
	Player(const std::string& name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();
};

