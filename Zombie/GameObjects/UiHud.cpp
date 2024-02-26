#include "pch.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name) : GameObject(name)
{
}

void UiHud::SetResolution(const sf::Vector2f resolution)
{
}

void UiHud::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UiHud::SetHiScore(int s)
{
	textHiScore.SetString(formatHighScore + std::to_string(s));
}

void UiHud::SetAmmo(int current,  int total)
{
	textAmmo.SetString(std::to_string(current) + "/" + std::to_string(total));
	// std::string text = formatAmmo.replace(formatAmmo.find("{0}"), 3, std::to_string(current));
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });
}

void UiHud::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

void UiHud::Init()
{
	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();

	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");

	float textSize = 60.f;
	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);

	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");
	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpSize);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);

	// Top
	float topY = 100.f;
	textScore.SetPosition({ 150.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 150.f, topY });

	// Bottom
	float BottomY = referenceResolution.y - 100.f;
	imgAmmoIcon.SetPosition({ 100.f, BottomY });
	textAmmo.SetPosition({ 300.f, BottomY });
	gaugeHp.setPosition({ 600.f, BottomY });

	textWave.SetPosition({ referenceResolution.x - 500.f, BottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 150.f, BottomY });
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
}

void UiHud::Update(float dt)
{
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::FixedUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	textAmmo.Draw(window);
	textWave.Draw(window);
	textZombieCount.Draw(window);
	window.draw(gaugeHp);
}
