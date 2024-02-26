#pragma once
#include "SpriteGo.h"

class SceneGame;
class Item;
class UiHud;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.f, 0.f };
	float speed = 500.f;

	int maxHp = 1000;
	int hp;
	int maxAmmo = 20;
	int ammo = maxAmmo;
	int maxMagazine = 6;
	int magazine = maxMagazine;

	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTimer = 0.f;
	float noDamageInterval = 3.f;

	SceneGame* sceneGame = nullptr;
	UiHud* uiHud = nullptr;

	bool isFiring = false;
	float fireInterval = 0.5f;
	float fireTimer = 0.f;
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;

public:
	Player(const std::string& name = "");
	~Player() override = default;

	const int GetPlayerHP() { return hp; }
	const int GetPlayerMaxHP() { return maxHp; }
	const int GetPlayerAmmo() { return ammo; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire ();

	void OnDamage(int damage);
	void OnDie();
	void OnItem(Item* item);
};

