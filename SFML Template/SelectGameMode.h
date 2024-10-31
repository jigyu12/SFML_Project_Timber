#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"

class SelectGameMode : public Scene
{
protected:
	TextGo* subMessage;
	SpriteGo* spriteMode;
public:
	SelectGameMode();
	~SelectGameMode() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void SetSubMessage(const std::string& msg);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

