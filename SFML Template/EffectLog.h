#pragma once
#include "SpriteGo.h"
class EffectLog : public SpriteGo
{
protected:
	sf::Vector2f gravity = { 0.f, 1000.f };
	sf::Vector2f velocity;

	float duration = 3.f;
	float timer = 0.f;

public:
	EffectLog();
	EffectLog(const std::string& texId, const std::string& name = "");
	~EffectLog() = default;

	void Update(float dt) override;

	void Fire(sf::Vector2f v);
};

