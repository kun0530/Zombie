#include "pch.h"
#include "SceneDev2.h"
#include "rapidcsv.h"

SceneDev2::SceneDev2(SceneIds id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	/*rapidcsv::Document doc("tables/colrowhdr.csv");

	std::vector<float> col = doc.GetColumn<float>("Open");
	std::cout << "Read " << col.size() << " values." << std::endl;

	for (const auto& v : col)
	{
		std::cout << v << std::endl;
	}*/
	
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev1);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		std::cout << STRING_TABLE->Get("HI") << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		STRING_TABLE->Load(Languages::Korean);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		STRING_TABLE->Load(Languages::English);
	}
}
