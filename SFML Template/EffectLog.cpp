#include "stdafx.h"
#include "EffectLog.h"

EffectLog::EffectLog()
	: SpriteGo("graphics/log.png")
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

EffectLog::EffectLog(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void EffectLog::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{ 
		SetActive(false);
		return;
	}

	velocity += gravity * dt;
	SetPosition(position + velocity * dt);
}

void EffectLog::Fire(sf::Vector2f v)
{
	velocity = v;
	timer = 0.f;
}
