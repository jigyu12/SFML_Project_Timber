#include "stdafx.h"
#include "Player.h"
#include "SceneDev1.h"	
#include "SceneDev2.h"	

Player::Player(PlayerSelect select, const std::string& name)
	: GameObject(name), playerSelect(select)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	if (name == "Player1")
	{
		LeftKey = sf::Keyboard::A;
		RightKey = sf::Keyboard::D;
	}
	else
	{
		LeftKey = sf::Keyboard::Left;
		RightKey = sf::Keyboard::Right;
	}
}

void Player::SetSide(Sides s)
{
	side = s;

	if (side == Sides::Left)
	{
		SetScale({ -1.f,1.f });
		spriteFire.setScale({ -1.f,1.f });
	}
	else if (side == Sides::Right)
	{
		SetScale({ 1.f,1.f });
		spriteFire.setScale({ 1.f,1.f });
	}

	sf::Vector2f newPos = position + localPosPlayer[(int)s];
	spritePlayer.setPosition(newPos);
	spriteFire.setPosition(newPos);
	spriteAxe.setPosition(newPos + localPosAxe);
	spriteRip.setPosition(newPos + localRipAxe);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(side);
}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	spritePlayer.setScale(this->scale);

	sf::Vector2f axeScale = this->scale;
	axeScale.x *= -1.f;
	spriteAxe.setScale(axeScale);

	sf::Vector2f axeRip = this->scale;
	axeRip.x = abs(axeScale.x);
	spriteRip.setScale(axeRip);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spritePlayer, preset);
		Utils::SetOrigin(spriteFire, preset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePlayer.setOrigin(origin);
	spriteFire.setOrigin(origin);
}

void Player::Init()
{
	if (playerSelect == PlayerSelect::Player1)
	{
		spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	}
	if (playerSelect == PlayerSelect::Player2)
	{
		spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer2));
	}
	SetOrigin(Origins::BC);

	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteAxe.setOrigin(originAxe);

	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	Utils::SetOrigin(spriteRip, Origins::BC);

	spriteFire.setTexture(TEXTURE_MGR.Get(texIdFire));
	Utils::SetOrigin(spriteFire, Origins::BC);
}

void Player::Reset()
{
	sfxChop.setBuffer(SOUNDBUFFER_MGR.Get(sbIdChop));
	sfxEat.setBuffer(SOUNDBUFFER_MGR.Get(sbIdEat));
	sfxStar.setBuffer(SOUNDBUFFER_MGR.Get(sbIdStar));

	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	spriteFire.setTexture(TEXTURE_MGR.Get(texIdFire));

	isAlive = true;
	isChppoing = false;
	life = 5.f;
	SetPosition(position);
	SetScale({ 1.f, 1.f });
	SetSide(Sides::Right);
	//if (playerSelect == PlayerSelect::Player1)
	//	SetSide(Sides::Right);
	//else if (playerSelect == PlayerSelect::Player2)
	//	SetSide(Sides::Left);
}


void Player::Release()
{
}


void Player::Update(float dt)
{
	if (!isAlive || !SCENE_MGR.GetIsGaming())
		return;

	appleTimer = Utils::Clamp(appleTimer - dt, 0.f, 4.f);
	godMode = Utils::Clamp(godMode - dt, 0.f, 10.f);
	if (godMode <= 0.f)
	{
		sfxStar.stop();
	}

	if (appleTimer <= 0.f)
	{
		SetApple(1.f);
	}
	if (life <= 0.f)
	{
		isAlive = false;
		//Ȳ�Կ� ToDo - 2�÷��̾� ���� �߰��ؾ���
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnDie(true);
	}

	AddLife(-dt * timeScale);

	if (InputMgr::GetKeyDown(LeftKey))
	{
		isChppoing = true;
		SetSide(Sides::Left);

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnChop(Sides::Left);
		else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
		{
			dynamic_cast<SceneDev2*>(sceneGame)->OnChop(Sides::Left, this);
		}
		sfxChop.play();
	}

	if (InputMgr::GetKeyUp(LeftKey))
	{
		isChppoing = false;
	}

	if (InputMgr::GetKeyDown(RightKey))
	{
		isChppoing = true;
		SetSide(Sides::Right);

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnChop(Sides::Right);
		else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
		{
			dynamic_cast<SceneDev2*>(sceneGame)->OnChop(Sides::Right, this);
		}

		sfxChop.play();
	}

	if (InputMgr::GetKeyUp(RightKey))
	{
		isChppoing = false;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	if (isAlive)
	{
		if (godMode > 0.f)
		{
			window.draw(spriteFire);
		}
		window.draw(spritePlayer);
		if (isChppoing)
		{
			window.draw(spriteAxe);
		}
	}
	else
	{
		window.draw(spriteRip);
	}
}

void Player::SetSceneGame(Scene* scene)
{
	sceneGame = scene;
}

void Player::Chopped(Sides side, BranchStatus branch)
{
	if (this->side == side)
	{
		switch (branch)
		{
		case BranchStatus::Normal:
			if (godMode <= 0.f)
			{
				isAlive = false;
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
					dynamic_cast<SceneDev1*>(sceneGame)->OnDie(false);
				//Ȳ�Կ� Todo - 2�÷��̾� ���� �߰��ؾ���
				else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
					dynamic_cast<SceneDev2*>(sceneGame)->OnDie(false, this);
			}
			else
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
					dynamic_cast<SceneDev1*>(sceneGame)->AddScore(50);
				//Ȳ�Կ� Todo - 2�÷��̾� ���� �߰��ؾ���
				AddLife(0.5f);
			}
			break;
		case BranchStatus::Apple:
			sfxEat.play();
			SetApple(0.5f);
			break;
		case BranchStatus::GoldenApple:
			sfxStar.play();
			SetGodMode(2.f);
			break;
		case BranchStatus::BeeHive:
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
				dynamic_cast<SceneDev1*>(sceneGame)->OnBeehive(side);
			else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
				dynamic_cast<SceneDev2*>(sceneGame)->OnBeehive(side, this);
			break;
		}
	}
	else
	{
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->AddScore(100);
		//Ȳ�Կ� Todo - 2�÷��̾� ���� �߰��ؾ���
		AddLife(1.f);
	}
}

void Player::SetGodMode(float godModeTime)
{
	godMode = Utils::Clamp(godMode + godModeTime, 0.f, 10.f);
	if (side == Sides::Left)
	{
		SetScale({ -1.f , 1.f });
	}
	else if (side == Sides::Right)
	{
		SetScale({ 1.f,1.f });
	}
}

void Player::SetApple(float timeScale)
{
	this->timeScale = timeScale;
	appleTimer = 4.f;
}

void Player::AddLife(float iLife)
{
	life = Utils::Clamp(life + iLife, 0.f, 5.f);
}
