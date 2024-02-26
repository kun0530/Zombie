#pragma once
#include "GameObject.h"

class SceneGame;

class Spawner : public GameObject
{
protected:
	float interval = 5.f;
	int spawnCount = 1.f;
	float radius = 250.f;

	float timer = 0.f;

	SceneGame* sceneGame = nullptr;

public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	virtual GameObject* Create() = 0;
	
	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
};

