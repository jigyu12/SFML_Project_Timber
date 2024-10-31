#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"


class SelectCharacter : public Scene
{
protected:
	TextGo* gameMessage;
	SpriteGo* player;
	SpriteGo* player2;

	

public:
	SelectCharacter();
	~SelectCharacter() = default;

	static std::string player1Select;
	static std::string player2Select;
	

	void Init() override;
	void Enter() override;
	void Exit() override;

	void SetGameMessage(const std::string& msg);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};