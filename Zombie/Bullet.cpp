#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"

Bullet::Bullet(const std::string& name) : SpriteGo(name)
{
}

void Bullet::Fire(const sf::Vector2f& dir, float s)
{
	direction = dir;
	speed = s;

	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
}

void Bullet::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	if (sceneGame != nullptr)
	{
		if (!sceneGame->IsInTileMap(position))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);
		}
	}
}