#include "pch.h"
#include "ZombieSpawner.h"
#include "TileMap.h"

ZombieSpawner::ZombieSpawner(const std::string& name) : GameObject(name)
{
}

void ZombieSpawner::Init()
{
	GameObject::Init();
}

void ZombieSpawner::Release()
{
	GameObject::Release();
}

void ZombieSpawner::Reset()
{
	GameObject::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	interval = 1.f;
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
}

void ZombieSpawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;

		sf::FloatRect tileMapBounds = tileMap->GetGlobalBounds();
		if (tileMap != nullptr)
		{
			const sf::Vector2f tileSize = tileMap->GetCellSize();
			tileMapBounds.left += tileSize.x;
			tileMapBounds.top += tileSize.y;
			tileMapBounds.width -= tileSize.x * 2.f;
			tileMapBounds.height -= tileSize.y * 2.f;
		}

		for (int i = 0; i < spawnCount; ++i)
		{
			// sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;
			sf::Vector2f pos(Utils::RandomRange(tileMapBounds.left, tileMapBounds.left + tileMapBounds.width),
				Utils::RandomRange(tileMapBounds.top, tileMapBounds.top + tileMapBounds.height));
			Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
			
			Zombie* zombie = Zombie::Create(zombieType);
			zombie->Init();
			zombie->Reset();
			zombie->SetPosition(pos);

			SCENE_MGR.GetCurrentScene()->AddGo(zombie);
		}
	}
}
