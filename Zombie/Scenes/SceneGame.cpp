#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "TextGo.h"
#include "UiHud.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return Utils::Clamp(point, rect);
}

int SceneGame::AddScore(const int score)
{
	this->score += score;
	return this->score;
}

void SceneGame::Init()
{
	// 배경
	tileMap = new TileMap("Background");
	AddGo(tileMap);

	// 스포너
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ItemSpawner());
	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomInUnitCircle() * 250.f);
		AddGo(s);
	}
	
	// 플레이어
	player = new Player("Player");
	AddGo(player);

	crosshair = new SpriteGo("Crosshair");
	crosshair->sortLayer = -1;
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->SetOrigin(Origins::MC);
	AddGo(crosshair, Layers::Ui);
	
	// UI
	uiHud = new UiHud("UI HUD");
	AddGo(uiHud, Layers::Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

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

	player->SetPosition({ 0.f,0.f });

	// UI
	uiHud->SetScore(score);
	uiHud->SetHiScore(100);
	// uiHud->SetAmmo(3, 8);
	// uiHud->SetHp(player->GetPlayerHP(), player->GetPlayerMaxHP());
	uiHud->SetWave(3);
	uiHud->SetZombieCount(7);
}

void SceneGame::Exit()
{
	Scene::Exit();

	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);

	Scene::Update(dt);

	crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));

	worldView.setCenter(player->GetPosition());
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
