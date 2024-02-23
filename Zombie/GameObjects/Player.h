#pragma once
#include "SpriteGo.h"

class TileMap;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.f, 0.f };
	float speed = 500.f;

	TileMap* tileMap = nullptr;

public:
	Player(const std::string& name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

