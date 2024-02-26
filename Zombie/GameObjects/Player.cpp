#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Item.h"
#include "UiHud.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = fireInterval;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("UI HUD"));

	hp = maxHp;
	isAlive = true;

	uiHud->SetHp(hp, maxHp);
	uiHud->SetAmmo(magazine, ammo);
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;

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
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		if (ammo < maxMagazine)
		{
			magazine += ammo;
			if (magazine > maxMagazine)
				magazine = maxMagazine;
			ammo = 0;
		}
		else
		{
			magazine = maxMagazine;
			ammo -= maxMagazine;
		}
		uiHud->SetAmmo(magazine, ammo);
	}

	fireTimer += dt;
	if (isFiring && fireTimer > fireInterval && magazine > 0)
	{
		Fire();
		--magazine;
		fireTimer = 0.f;

		uiHud->SetAmmo(magazine, ammo);
	}

	if (isNoDamage)
	{
		noDamageTimer += dt;
		if (noDamageTimer > noDamageInterval)
		{
			isNoDamage = false;
		}
	}
}

void Player::FixedUpdate(float dt)
{
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();

	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);
}

void Player::OnDamage(int damage)
{
	if (!isAlive || isNoDamage)
		return;

	hp -= damage;

	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}

	uiHud->SetHp(hp, maxHp);
}

void Player::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetTexture("graphics/blood.png");
}

void Player::OnItem(Item* item)
{
	switch (item->GetType())
	{
	case Item::Types::Ammo:
		ammo += item->GetValue();
		if (ammo > maxAmmo)
			ammo = maxAmmo;
		uiHud->SetAmmo(magazine, ammo);
		break;
	case Item::Types::Health:
		hp += item->GetValue();
		if (hp > maxHp)
			hp = maxHp;
		uiHud->SetHp(hp, maxHp);
		break;
	}
}