#pragma once
#include "SpriteGo.h"
#include "Player.h"

class SceneGame;
class UiHud;

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

	int damage;
	float attackInterval;
	float attackTimer = 0.f;

	int maxHp;
	float speed;
	int hp;

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
	UiHud* uiHud = nullptr;

	sf::Vector2f direction;
	bool isAlive = true;

	Zombie(const std::string& name = ""); // �ܺο��� ���� ���� ���ϵ���

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	void OnDamage(int damage);
	void OnDie();
};

