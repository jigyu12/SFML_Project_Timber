#include "stdafx.h"
#include "SelectGameMode.h"

SelectGameMode::SelectGameMode()
	:Scene(id)
{
}

void SelectGameMode::Init()
{
	subMessage = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "SUB"));
	Scene::Init();

	subMessage->text.setCharacterSize(70);
	subMessage->text.setFillColor(sf::Color::Red);
	SetSubMessage("If You Wanna Play Solo Press [1]\n If You Wanna play Duel Press [2]\n Press ESC TO MAINTITLE");
	subMessage->SetPosition({ 1920.f / 2,1080.f / 2 });
}

void SelectGameMode::Enter()
{
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SelectGameMode::Exit()
{
	Scene::Exit();

	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SelectGameMode::SetSubMessage(const std::string& msg)
{
	subMessage->text.setString(msg);
	subMessage->SetOrigin(Origins::MC);
}

void SelectGameMode::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.SetGameMode(SceneIds::Dev1);
		SCENE_MGR.ChangeScene(SceneIds::SelectCharacter);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.SetGameMode(SceneIds::Dev2);
		SCENE_MGR.ChangeScene(SceneIds::SelectCharacter);
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::MainTitle);
	}
}

void SelectGameMode::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
