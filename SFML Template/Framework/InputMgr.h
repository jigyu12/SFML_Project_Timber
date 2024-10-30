#pragma once

class InputMgr
{
public:
	enum class KeyStatus
	{
		None,
		Down,
		Held,
		Up,
	};

private:
	static std::vector<KeyStatus> inputs;
	static sf::Vector2i mousePosition;

public:
	static void Init();

	static void Clear();
	static void UpdateEvent(const sf::Event& ev);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);

	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButton(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);

	static sf::Vector2i GetMousePosition()  { return mousePosition;  }
};

