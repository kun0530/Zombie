#include "pch.h"
#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(const std::string& name) : Spawner(name)
{
}


GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];

	return Zombie::Create(zombieType);
}

void ZombieSpawner::Reset()
{
	Spawner::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	interval = 5.f;
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;
}