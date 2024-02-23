#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler
	};
	static const int TotalTypes = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;

	sf::Vector2f look = { 1.f, 0.f };

	bool isDead = false;
	int maxHp;
	float speed;
	int hp;

	Player* player;

	sf::Vector2f direction;
	sf::FloatRect zombieBounds;

	Zombie(const std::string& name = ""); // 외부에서 좀비를 생성 못하도록

public:
	~Zombie() override = default;

	void SetIsDead(const bool isDead) { this->isDead = isDead; }
	bool IsDead() { return isDead; }
	sf::FloatRect& GetZombieBounds();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

