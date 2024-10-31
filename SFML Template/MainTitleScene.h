#pragma once
#include "Scene.h"
#include "TextGo.h"


class MainTitleScene : public Scene
{
protected:
	TextGo* mainMassage;

public:
	MainTitleScene();
	~MainTitleScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void SetMainMassage(const std::string& msg);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};