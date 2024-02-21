#include "pch.h"
#include "Zombie.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie();

	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		break;
	case Zombie::Types::Chase:
		zombie->textureId = "graphics/chase.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 20;
		zombie->speed = 50;
		break;
	}

	return nullptr;
}

Zombie::Zombie(const std::string& name) : SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
