#include "stdafx.h"

std::vector<InputMgr::KeyStatus> InputMgr::inputs;
sf::Vector2i InputMgr::mousePosition;

void InputMgr::Init()
{
	inputs.resize(sf::Keyboard::KeyCount + sf::Mouse::ButtonCount);
}

void InputMgr::Clear()
{
	for (auto& status : inputs)
	{
		switch (status)
		{
		case KeyStatus::Up:
			status = KeyStatus::None;
			break;
		case KeyStatus::Down:
			status = KeyStatus::Held;
			break;
		}
	}
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (inputs[ev.key.code] == KeyStatus::None)
		{
			inputs[ev.key.code] = KeyStatus::Down;
		}
		break;
	case sf::Event::KeyReleased:
		inputs[ev.key.code] = KeyStatus::Up;
		break;
	case sf::Event::MouseButtonPressed:
	{
		int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
		if (inputs[code] == KeyStatus::None)
		{
			inputs[code] = KeyStatus::Down;
		}
	}
		break;
	case sf::Event::MouseButtonReleased:
		inputs[sf::Keyboard::KeyCount + ev.mouseButton.button] = KeyStatus::Up;
		break;
	case sf::Event::MouseMoved:
		mousePosition.x = ev.mouseMove.x;
		mousePosition.y = ev.mouseMove.y;
		break;
	}
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return inputs[key] == KeyStatus::Down;
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return inputs[key] == KeyStatus::Held || inputs[key] == KeyStatus::Down;
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return inputs[key] == KeyStatus::Up;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return inputs[code] == KeyStatus::Down;
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return inputs[code] == KeyStatus::Held || inputs[code] == KeyStatus::Down;
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return inputs[code] == KeyStatus::Up;
}

