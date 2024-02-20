#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	// Math
	static float SqrtMagnitude(const sf::Vector2f& vec); // 길이의 제곱
	static float Magnitude(const sf::Vector2f& vec); // 벡터의 길이
	static void Normalize(sf::Vector2f& vec); // 단위 벡터로 변환
	static sf::Vector2f GetNormal(const sf::Vector2f& vec); // 단위 벡터를 반환
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2); // 두 점 사이의 거리

	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);

	static float Angle(const sf::Vector2f& vec);
};