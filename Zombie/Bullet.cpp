#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(const std::string& name) : GameObject(name)
{
}

void Bullet::SetDirection(const sf::Vector2f& dir)
{
	direction = dir;
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	bullet.setPosition(pos);
}

void Bullet::Translate(const sf::Vector2f& delta)
{
	position += delta;
	SetPosition(position);
}

sf::FloatRect& Bullet::GetBulletBounds()
{
	bulletBounds = bullet.getGlobalBounds();
	return bulletBounds;
}

void Bullet::Init()
{
	GameObject::Init();

	bullet.setRadius(5.f);
	// SetPosition({ 0.f, 0.f });
	bullet.setFillColor(sf::Color::Yellow);
	SetOrigin(Origins::MC);
}

void Bullet::Release()
{
	GameObject::Release();
}

void Bullet::Reset()
{
	GameObject::Reset();

	timer = 0.f;
}

void Bullet::Update(float dt)
{
	GameObject::Update(dt);

	Translate(direction * speed * dt);

	timer += dt;
	if (timer >= duration)
	{
		timer = 0.f;
		SetActive(false);
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	window.draw(bullet);
}
