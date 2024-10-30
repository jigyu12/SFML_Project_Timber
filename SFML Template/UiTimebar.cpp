#include "stdafx.h"
#include "UiTimebar.h"

UiTimebar::UiTimebar(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::UI;
}

void UiTimebar::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	shape.setPosition(pos);
}

void UiTimebar::SetScale(const sf::Vector2f& s)
{
	scale = s;
	shape.setScale(scale);
}

void UiTimebar::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(shape, originPreset);
	}
}

void UiTimebar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	shape.setOrigin(origin);
}

void UiTimebar::Reset()
{
	SetValue(1.0f);
}

void UiTimebar::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void UiTimebar::Set(const sf::Vector2f size, const sf::Color& color)
{
	currentSize = maxSize = size;
	shape.setFillColor(color);
	SetValue(1.0f);
}

void UiTimebar::SetValue(float value)
{
	value = Utils::Clamp(value, 0.f, 1.f);
	currentSize.x = maxSize.x * value;
	shape.setSize(currentSize);
	SetOrigin(originPreset);
}
