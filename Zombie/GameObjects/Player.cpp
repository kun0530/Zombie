#include "pch.h"
#include "Player.h"

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
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = mousePos; // TO-DO: ���߿� ����!

	look = mouseWorldPos - position;
	Utils::Normalize(look);

	float angle = Utils::Angle(look);
	sprite.setRotation(angle);

	// �����¿�(WASD) �̵�
	sf::Vector2f playerPos = GetPosition();
	playerPos.x += InputMgr::GetAxis(Axis::Horizontal) * speed * dt;
	playerPos.y += InputMgr::GetAxis(Axis::Vertical) * speed * dt;
	SetPosition(playerPos);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
