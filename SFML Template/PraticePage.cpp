#include "stdafx.h"
#include "PraticePage.h"



PraticePage::PraticePage()
	:Scene(SceneIds::PraticePage)
{
}

void PraticePage::Init()
{
	Message = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "text"));
	player1 = AddGo(new SpriteGo("graphics/player.png"));
	player2 = AddGo(new SpriteGo("graphics/player2.png"));
	arrow = AddGo(new SpriteGo("graphics/arrow.png"));


	Scene::Init();
	Message->text.setCharacterSize(150);
	SetMessage("Select Player");
	Message->SetPosition({ 1920.f / 2 ,1080.f / 3 });



	player1->SetPosition(player1pos);
	player1->SetOrigin(Origins::MC);

	player2->SetPosition(player2pos);
	player2->SetOrigin(Origins::MC);

	arrow->SetScale({ 0.05f,0.05f });
	arrow->SetPosition(player1pos - arrowXoffset);
	arrow->SetOrigin(Origins::MC);

}

void PraticePage::Enter()
{

	TEXTURE_MGR.Load("graphics/arrow.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void PraticePage::Exit()
{
	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/arrow.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void PraticePage::Setarrowside(Sides s)
{
	arrowside = s;

	if (arrowside == Sides::Left)
	{
		arrow->SetScale({ 0.05f,0.05f });
		arrow->SetOrigin(Origins::MC);
		arrow->SetPosition(player1pos - arrowXoffset);
	}
	else if (arrowside == Sides::Right)
	{
		arrow->SetScale({ 0.05f,0.05f });
		arrow->SetOrigin(Origins::MC);
		arrow->SetPosition(player2pos - arrowXoffset);
	}
}


void PraticePage::SetMessage(const std::string& msg)
{
	Message->text.setString(msg);
	Message->SetOrigin(Origins::MC);
}

void PraticePage::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		Setarrowside(Sides::Left);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		Setarrowside(Sides::Right);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		if (Getarrowside() == Sides::Left)
		{
			SCENE_MGR.player1sprite = PlayerSelect::Player1;
			SCENE_MGR.ChangeScene(SCENE_MGR.GetGameMode());
		}
		else if (Getarrowside() == Sides::Right)
		{
			SCENE_MGR.player1sprite = PlayerSelect::Player2;
			SCENE_MGR.ChangeScene(SCENE_MGR.GetGameMode());
		}

	}
}

void PraticePage::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
