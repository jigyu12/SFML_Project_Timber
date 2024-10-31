#include "stdafx.h"
#include "MainTitleScene.h"

MainTitleScene::MainTitleScene()
	: Scene(SceneIds::MainTitle)
{
}

void MainTitleScene::Init()
{

	mainMassage = AddGo(new TextGo("fonts/KOMIKAP_.ttf","Main"));
	Scene::Init();


	mainMassage->text.setCharacterSize(100);
	mainMassage->text.setFillColor(sf::Color::Blue);
	SetMainMassage("      Game Start!!!!!!!\nPress Space to Start!!!");
	mainMassage->SetPosition({ 1920.f / 2,1080.f / 2 });
	
}

void MainTitleScene::Enter()
{
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void MainTitleScene::Exit()
{
	Scene::Exit();

	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void MainTitleScene::SetMainMassage(const std::string& msg)
{
	mainMassage->text.setString(msg);
	mainMassage->SetOrigin(Origins::MC);
}

void MainTitleScene::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::SelectGameMode);
	}
}

void MainTitleScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
