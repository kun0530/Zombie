#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va;
	std::string spriteSheetId;
	sf::Texture* texture;

	sf::Vector2i cellCount; // ���� ������, ������ ����
	sf::Vector2f cellSize; // ���� ���� ����, ���� ����

public:
	TileMap(const std::string& name = "");

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void SetSpriteSheetId(const std::string& id);

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetScale(const sf::Vector2f& scale) override;

	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

