#include "pch.h"
#include "Zombie.h"

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

sf::FloatRect& Zombie::GetZombieBounds()
{
	zombieBounds = sprite.getGlobalBounds();
	return zombieBounds;
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
	sortLayer = 2;
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	isDead = false;
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void Zombie::Update(float dt)
{
	if (isDead)
		return;

	SpriteGo::Update(dt);

	direction = player->GetPosition() - position;
	float distance = Utils::Magnitude(direction);

	float angle = Utils::Angle(direction);
	SetRotation(angle);

	Utils::Normalize(direction);
	Translate(direction * speed * dt);

	// ºö~~~~
	/*float playerAngle = Utils::Angle(-player->GetLook());
	if (InputMgr::GetMouseButton(sf::Mouse::Left)
		&& std::abs(playerAngle - angle) <= 10.f)
	{
		isDead = true;
		SetTexture("graphics/blood.png");
	}*/

	//if (distance < 50.f) // ¼÷Á¦
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	//}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
