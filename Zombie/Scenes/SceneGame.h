#pragma once
#include "Scene.h"

class TileMap;
class Player;
class Spawner;
class UiHud;
class SpriteGo;

class SceneGame : public Scene
{
protected:
	TileMap* tileMap = nullptr;
	Player* player = nullptr;
	UiHud* uiHud = nullptr;
	SpriteGo* crosshair = nullptr;

	std::list<GameObject*> zombieList;
	std::vector<Spawner*> spawners;

	int score = 0;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	bool IsInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f point);
	const std::list<GameObject*>& GetZombieList() const { return zombieList; }

	UiHud* GetHud() const { return uiHud; }

	int AddScore(const int score);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

