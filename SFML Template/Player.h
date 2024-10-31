#pragma once
#include "GameObject.h"

class SceneDev1;
class SceneDev2;

class Player : public GameObject
{
protected:
	sf::Sound sfxChop;

	PlayerSelect playerSelect = PlayerSelect::None;

	sf::Sprite spritePlayer;
	sf::Sprite spriteAxe;
	sf::Sprite spriteRip;
	sf::Sprite spriteFire;

	std::string sbIdChop = "sound/chop.wav";
	std::string texIdFire = "graphics/fire.png";
	std::string texIdPlayer = "graphics/player.png";
	std::string texIdAxe = "graphics/axe.png";
	std::string texIdRip = "graphics/rip.png";

	Sides side = Sides::Right;

	sf::Vector2f localPosPlayer[3] = { { -300.f, 0.f },  { 300.f, 0.f },  { 0.f, 0.f } };
	sf::Vector2f localPosAxe = { 0.f, -70.f };
	sf::Vector2f localRipAxe = { 0.f, 0.f };

	sf::Vector2f originAxe = { -65.f, 0.f };

	bool isAlive = true;
	bool isChppoing = false;
	float godMode = 0.f;
	float timeScale = 1.f;
	float appleTimer = 0.f;

	Scene* sceneGame = nullptr;

public:
	Player(PlayerSelect select, const std::string& name = "");
	virtual ~Player() = default;
	void SetTexture(const std::string& texid);
	Sides GetSide() const { return side; }
	void SetSide(Sides s);
	void OnDie();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;

	void SetSceneGame(Scene* scene);

	void Player1Update(float dt);
	void Player2Update(float dt);

	float GetGodMode() const { return godMode; }
	void SetGodMode(float time);
	
	float GetPlayerTimeScale() const { return timeScale; }
	void SetPlayerTimeScale(float timescale);
};

