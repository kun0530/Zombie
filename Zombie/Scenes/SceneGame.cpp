#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "Bullet.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

void SceneGame::Init()
{
	TileMap* tileMap = new TileMap("Background");
	AddGo(tileMap);

	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());
	for (auto s : spawners)
	{
		s->SetPosition(sf::Vector2f(0.f, 0.f));
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	wave = 1;

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	// 테스트 코드
	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f,0.f });
	tileMap->SetOrigin(Origins::MC);
	/*tileMap->SetScale({ 2.f, 2.f });
	tileMap->SetRotation(45);*/

	player->SetMapBounds(tileMap->GetMapBounds());
	player->SetPosition({ 0.f,0.f });

	for (auto s : spawners)
	{
		s->SetMapBounds(tileMap->GetMapBounds());
	}
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	// 테스트 코드: 레이어
	/*if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
		tileMap->sortLayer = 2;
		ResortGo(tileMap);
	}*/

	bulletTimer += dt;
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && bulletTimer >= rateOfFire)
	{
		bulletTimer = 0.f;
		FireBullet();
	}

	auto it = useBulletList.begin();
	while (it != useBulletList.end())
	{
		Bullet* bullet = *it;
		if (!bullet->GetActive())
		{
			gameObjects.remove(*it);
			it = useBulletList.erase(it);
			unuseBulletList.push_back(bullet);
			continue;
		}
		else
		{
			++it;
		}

		
		std::list<GameObject*> zombieList;
		FindGoAll("Zombie", zombieList);
		for (auto zombieGo : zombieList)
		{
			Zombie* zombie = dynamic_cast<Zombie*>(zombieGo);
			if (zombie->GetZombieBounds().intersects(bullet->GetBulletBounds()) && !zombie->IsDead())
			{
				/*SpriteGo* blood = new SpriteGo("Blood");
				blood->SetTexture("graphics/blood.png");
				blood->SetPosition(zombie->GetPosition());
				blood->sortLayer = 1;
				AddGo(blood);

				zombie->SetActive(false);*/

				// RemoveGo(zombie);

				zombie->SetIsDead(true);
				zombie->SetTexture("graphics/blood.png");
				zombie->sortLayer = 1;
				ResortGo(zombie);

				bullet->SetActive(false);
				break;
			}
		}
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

// Timber에서 가져옴
void SceneGame::FireBullet()
{
	Bullet* bullet = nullptr;
	if (unuseBulletList.empty())
	{
		bullet = new Bullet();
		bullet->Init();
	}
	else
	{
		bullet = unuseBulletList.front();
		unuseBulletList.pop_front();
	}

 	bullet->SetActive(true);
	bullet->Reset();
	bullet->SetPosition(player->GetPosition());

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = ScreenToWorld(mousePos);
	bullet->SetDirection(Utils::GetNormal(mouseWorldPos - player->GetPosition()));

	useBulletList.push_back(bullet);
	AddGo(bullet);
}