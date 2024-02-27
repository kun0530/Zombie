#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "SpriteGoEffect.h"
#include "ZombieTable.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("Zombie");
	zombie->type = zombieType;

	const DataZombie& data = ZOMBIE_TABLE->Get(zombieType);
	zombie->textureId = data.textureId;
	zombie->maxHp = data.maxHp;
	zombie->speed = data.speed;
	zombie->damage = data.damage;
	zombie->attackInterval = data.attackInterval;

	zombie->sortLayer = 1;

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
	attackTimer = attackInterval;

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("UI HUD"));

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

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnDamage(damage);
			attackInterval = 0.f;
		}
	}
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

	uiHud->SetScore(sceneGame->AddScore(10));
	uiHud->SetZombieCount(sceneGame->MinusZombieNum());
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);

	SpriteGoEffect* effectBlood = new SpriteGoEffect();
	effectBlood->Init();
	effectBlood->SetOrigin(Origins::MC);
	effectBlood->SetTexture("graphics/blood.png");
	effectBlood->Reset();
	effectBlood->sortLayer = -1;
	effectBlood->sortOrder = 1;
	effectBlood->SetPosition(position);
	effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));
	sceneGame->AddGo(effectBlood);
}