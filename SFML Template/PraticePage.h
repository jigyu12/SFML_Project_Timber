#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"


class PraticePage : public Scene
{
protected:
	TextGo* Message;
	SpriteGo* player1;
	SpriteGo* player2;
	SpriteGo* backGround;
	SpriteGo* arrow;
	
	Sides arrowside = Sides::Left;

	sf::Vector2f arrowXoffset = { 100.f, 0.0f };
	
	sf::Vector2f player1pos = { 1920.f / 3,1080 / 2 };
	sf::Vector2f player2pos = { 1920.f - 1920.f / 3,1080 / 2 };
	
public:

	Sides Getarrowside() const { return arrowside; }
	void Setarrowside(Sides s);
	PraticePage();
	~PraticePage() = default;


	void Init() override;
	void Enter() override;
	void Exit() override;

	void SetMessage(const std::string& msg);

	
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

