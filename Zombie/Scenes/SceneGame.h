#pragma once
#include "Scene.h"

class Player;
class ZombieSpawner;
class Bullet;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	std::vector<ZombieSpawner*> spawners;

	std::list<Bullet*> useBulletList;
	std::list<Bullet*> unuseBulletList;

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

