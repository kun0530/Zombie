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
	// ���
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	// ������
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ItemSpawner());
	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomInUnitCircle() * 250.f);
		AddGo(s);
	}
	
	// �÷��̾�
	player = new Player("Player");
	player->sortLayer = 1;
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

	// �׽�Ʈ �ڵ�
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
	uiHud->SetWave(wave);
	uiHud->SetZombieCount(zombieNum);
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

	switch (currStatus)
	{
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::NextWave:
		UpdateNextWave(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::UpdateGame(float dt)
{
	if (zombieNum <= 0)
	{
		SetStatus(Status::NextWave);
	}
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
	}

	// ���� �׽�Ʈ
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SOUND_MGR.PlayBgm("sound/mapleBgm1.mp3");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SOUND_MGR.PlayBgm("sound/mapleBgm2.mp3");
	}
}

void SceneGame::UpdateNextWave(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);

		++wave;
		zombieNum = wave * 2;

		player->SetPosition({ 0.f, 0.f });
		tileMap->Set({ wave * 10, wave * 10 }, { 50.f, 50.f });
		tileMap->SetOrigin(Origins::MC);

		uiHud->SetWave(wave);
		uiHud->SetZombieCount(zombieNum);
	}
}

void SceneGame::UpdateGameOver(float dt)
{
}

void SceneGame::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case Status::Game:
		uiHud->SetMessage("");
		uiHud->SetMessageActive(false);
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case Status::NextWave:
		uiHud->SetMessage("Next Wave!");
		uiHud->SetMessageActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::GameOver:
		uiHud->SetMessage("Game Over!");
		uiHud->SetMessageActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Pause:
		uiHud->SetMessage("Pause!");
		uiHud->SetMessageActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}
