#include "pch.h"
#include "Player.h"
#include "TileMap.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look);

	float angle = Utils::Angle(look);
	sprite.setRotation(angle);

	// 상하좌우(WASD) 이동
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
		Utils::Normalize(direction);

	sf::Vector2f pos = position + direction * speed * dt;
	/*if (tileMap != nullptr)
	{
		sf::FloatRect tileMapBounds = tileMap->GetGlobalBounds();
		const sf::Vector2f tileSize = tileMap->GetCellSize();
		tileMapBounds.left += tileSize.x;
		tileMapBounds.top += tileSize.y;
		tileMapBounds.width -= tileSize.x * 2.f;
		tileMapBounds.height -= tileSize.y * 2.f;

		pos.x = Utils::Clamp(pos.x, tileMapBounds.left, tileMapBounds.left + tileMapBounds.width);
		pos.y = Utils::Clamp(pos.y, tileMapBounds.top, tileMapBounds.top + tileMapBounds.height);
	}*/
	SetPosition(pos);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
