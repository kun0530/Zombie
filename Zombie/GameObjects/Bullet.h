#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
protected:
	sf::CircleShape bullet;
	
	sf::Vector2f direction;
	float speed = 1000.f;

	sf::FloatRect bulletBounds;

	float timer = 0.f;
	float duration = 3.f;

public:
	Bullet(const std::string& name = "");
	~Bullet() override = default;

	void SetDirection(const sf::Vector2f& dir);
	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;

	sf::FloatRect& GetBulletBounds();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};