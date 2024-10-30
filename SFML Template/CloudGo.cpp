#include "stdafx.h"
#include "CloudGo.h"

CloudGo::CloudGo(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void CloudGo::Reset()
{
	SpriteGo::Reset();

	speed = Utils::RandomRange(rangeSpeed.x, rangeSpeed.y);
	sf::Vector2f newPos;
	if (Utils::RandomValue() > 0.5f)
	{
		direction.x = 1.f;
		newPos.x = bounds.left;
	}
	else
	{
		direction.x = -1.f;
		newPos.x = bounds.left + bounds.width;
	}
	newPos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);
	SetPosition(newPos);

	float rand = Utils::RandomRange(rangeScale.x, rangeScale.y);
	sf::Vector2f newScale(rand, rand);
	newScale.x = abs(newScale.x);
	if (direction.x > 0)
	{
		newScale.x = -newScale.x;
	}
	SetScale(newScale);
}

void CloudGo::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	if (!IsWithinBounds())
	{
		Reset();
	}
}

bool CloudGo::IsWithinBounds() const
{
	auto globalBounds = sprite.getGlobalBounds();
	if (direction.x > 0 && globalBounds.left > bounds.left + bounds.width)
	{
		return false;
	}
	if (direction.x < 0 && globalBounds.left + globalBounds.width < bounds.left)
	{
		return false;
	}
	return true;
}