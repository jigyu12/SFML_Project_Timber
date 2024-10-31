#pragma once
#include "Scene.h"

class Tree;
class Player;
class TextGo;
class UiScore;
class UiTimebar;

class SceneDev2 : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	Status currentStatus = Status::Awake;

	Tree* tree1;
	Tree* tree2;
	Player* player1;
	Player* player2;

	TextGo* centerMsg1;
	TextGo* centerMsg2;
	UiTimebar* uiTimer1;
	UiTimebar* uiTimer2;

	float timer1 = 0.f;
	float timer2 = 0.f;
	float gameTime = 5.f;

	sf::Sound sfxDeath;
	sf::Sound sfxTimeOut;

	std::string sbIdDeath = "sound/death.wav";
	std::string sbIdTimeOut = "sound/out_of_time.wav";

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void SetCenterMessage(TextGo* textGo, const std::string& msg);
	void SetVisibleCenterMessage(TextGo* textGo, bool visible);

	void SetStatus(Status newStatus);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void OnChop(Sides side);
};