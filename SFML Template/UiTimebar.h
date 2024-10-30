#pragma once
#include "GameObject.h"
class UiTimebar : public GameObject
{
protected:
	sf::RectangleShape shape;

	sf::Vector2f maxSize;
	sf::Vector2f currentSize;

public:
	UiTimebar(const std::string& name = "");
	virtual ~UiTimebar() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void Set(const sf::Vector2f size, const sf::Color& color);
	float GetValue() const { return currentSize.x / maxSize.x; }
	void SetValue(float value);
};

