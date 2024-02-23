#include "pch.h"
#include "Zombie.h"
#include "TileMap.h"

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
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	direction = player->GetPosition() - position;
	float distance = Utils::Magnitude(direction);
	Utils::Normalize(direction);

	float angle = Utils::Angle(direction);
	SetRotation(angle);

	sf::Vector2f pos = position + direction * speed * dt;
	if (tileMap != nullptr)
	{
		sf::FloatRect tileMapBounds = tileMap->GetGlobalBounds();
		const sf::Vector2f tileSize = tileMap->GetCellSize();
		tileMapBounds.left += tileSize.x;
		tileMapBounds.top += tileSize.y;
		tileMapBounds.width -= tileSize.x * 2.f;
		tileMapBounds.height -= tileSize.y * 2.f;

		pos.x = Utils::Clamp(pos.x, tileMapBounds.left, tileMapBounds.left + tileMapBounds.width);
		pos.y = Utils::Clamp(pos.y, tileMapBounds.top, tileMapBounds.top + tileMapBounds.height);
	}
	SetPosition(pos);

	//if (distance < 50.f) // ¼÷Á¦
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	//}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
