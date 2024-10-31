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


	void Init() override;
	void Enter() override;
	void Exit() override;

	void SetGameMessage(const std::string& msg);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};