#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("Zombie");
	zombie->type = zombieType;

	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 20;
		zombie->speed = 50;
		break;
	}

	return zombie;
}

Zombie::Zombie(const std::string& name) : SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	isAlive = true;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;

	direction = player->GetPosition() - position;
	float distance = Utils::Magnitude(direction);
	Utils::Normalize(direction);

	float angle = Utils::Angle(direction);
	SetRotation(angle);

	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	if (!isAlive)
		return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Zombie::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);
	// SetTexture("graphics/blood.png");
}
