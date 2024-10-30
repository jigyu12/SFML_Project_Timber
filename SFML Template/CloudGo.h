#pragma once
#include "SpriteGo.h"

class CloudGo : public SpriteGo
{
protected:
	float speed;
	sf::Vector2f direction = { 1.0f, 0.f };
	sf::Vector2f rangeSpeed = { 100.f, 200.f };
	sf::Vector2f rangeScale = { 0.5f, 1.5f };
	sf::FloatRect bounds = { 0.f, 0.f, 1920.f, 500.f };

	bool IsWithinBounds() const;

public:
	CloudGo(const std::string& texId, const std::string& name = "");
	~CloudGo() = default;

	void SetRangeSpeed(const sf::Vector2f& speed) { this->rangeSpeed = speed; }
	void SetBounds(const sf::FloatRect& bounds) { this->bounds = bounds; }
	void SetRangeScale(const sf::Vector2f& scales) { this->rangeScale = scales; }

	void Reset() override;
	void Update(float dt) override;
};

