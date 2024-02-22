#pragma once
#include "Scene.h"

class Player;
class ZombieSpawner;
class Bullet;

class SceneGame : public Scene
{
protected:
	int wave = 1;

	Player* player = nullptr;
	std::vector<ZombieSpawner*> spawners;

	std::list<Bullet*> useBulletList;
	std::list<Bullet*> unuseBulletList;
	float bulletTimer = 0.f;
	float rateOfFire = 0.5f;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void FireBullet();
};

