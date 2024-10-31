#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	for (int i = 0; i < 3; ++i)
	{
		CloudGo* cloud = AddGo(new CloudGo("graphics/cloud.png"));
		cloud->sortingLayer = SortingLayers::Background;
		cloud->sortingOrder = 0;
	}

	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");

	tree1 = AddGo(new Tree("Tree1"));
	tree2 = AddGo(new Tree("Tree2"));
	player1 = AddGo(new Player(PlayerSelect::Player1, "Player1"));
	player2 = AddGo(new Player(PlayerSelect::Player2, "Player2"));

	centerMsg1 = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message1"));
	centerMsg1->sortingLayer = SortingLayers::UI;

	centerMsg2 = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message2"));
	centerMsg2->sortingLayer = SortingLayers::UI;

	uiTimer1 = AddGo(new UiTimebar("Ui Timer1"));
	uiTimer2 = AddGo(new UiTimebar("Ui Timer2"));

	Scene::Init();

	tree1->SetPosition({ 1920.f / 2 / 2, 1080.f - 200.f });
	player1->SetPosition({ 1920.f / 2 / 2, 1080.f - 200.f });

	tree2->SetPosition({ 1920.f / 2 / 2 * 3, 1080.f - 200.f });
	player2->SetPosition({ 1920.f / 2 / 2 * 3, 1080.f - 200.f });

	centerMsg1->text.setCharacterSize(100);
	centerMsg1->text.setFillColor(sf::Color::White);
	centerMsg1->SetPosition({ 1920.f / 2.f / 2.f, 1080.f / 2.f });

	centerMsg2->text.setCharacterSize(100);
	centerMsg2->text.setFillColor(sf::Color::White);
	centerMsg2->SetPosition({ 1920.f / 2.f / 2.f * 3, 1080.f / 2.f });

	uiTimer1->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer1->SetOrigin(Origins::ML);
	uiTimer1->SetPosition({ 1920.f / 2.f - 500.f, 1080.f - 100.f });

	uiTimer2->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer2->SetOrigin(Origins::ML);
	uiTimer2->SetPosition({ 1920.f / 2.f + 250.f, 1080.f - 100.f });
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load("sound/chop.wav");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));

	player1->SetSceneGame(this);
	player2->SetSceneGame(this);

	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;

	player1->SetSceneGame(nullptr);
	player2->SetSceneGame(nullptr);
	tree1->ClearEffectLog();
	tree2->ClearEffectLog();

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");

}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}

	switch (currentStatus)
	{
	case SceneDev2::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneDev2::Status::Game:
		UpdateGame(dt);
		break;
	case SceneDev2::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneDev2::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev2::SetCenterMessage(TextGo* textGo, const std::string& msg)
{
	textGo->text.setString(msg);
	textGo->SetOrigin(Origins::MC);
}

void SceneDev2::SetVisibleCenterMessage(TextGo* textGo, bool visible)
{
	textGo->SetActive(visible);
}

void SceneDev2::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneDev2::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(centerMsg1, true);
		SetVisibleCenterMessage(centerMsg2, true);
		SetCenterMessage(centerMsg1, "Press Enter To Start!!");
		SetCenterMessage(centerMsg2, "Press Enter To Start!!");
		timer1 = gameTime;
		timer2 = gameTime;
		uiTimer1->SetValue(1.f);
		uiTimer2->SetValue(1.f);
		break;
	case SceneDev2::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			timer1 = gameTime;
			timer2 = gameTime;

			uiTimer1->SetValue(1.f);
			uiTimer2->SetValue(1.f);

			player1->Reset();
			player2->Reset();
			tree1->Reset();
			tree2->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(centerMsg1,false);
		SetVisibleCenterMessage(centerMsg2,false);
		break;
	case SceneDev2::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(centerMsg1, true);
		SetVisibleCenterMessage(centerMsg2, true);
		break;
	case SceneDev2::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(centerMsg1, true);
		SetVisibleCenterMessage(centerMsg2, true);
		SetCenterMessage(centerMsg1,"PAUSE! ESC TO RESUME!");
		SetCenterMessage(centerMsg2,"PAUSE! ESC TO RESUME!");
		break;
	}
}

void SceneDev2::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev2::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}

	timer1 = Utils::Clamp(timer1 - dt, 0.f, gameTime);
	timer2 = Utils::Clamp(timer2 - dt, 0.f, gameTime);
	uiTimer1->SetValue(timer1 / gameTime);
	uiTimer2->SetValue(timer2 / gameTime);
	if (timer1 <= 0.f)
	{
		sfxTimeOut.play();

		player1->OnDie();
		SetCenterMessage(centerMsg1, "Time Over!");
		SetStatus(Status::GameOver);
		return;
	}

	if (timer2 <= 0.f)
	{
		sfxTimeOut.play();

		player2->OnDie();
		SetCenterMessage(centerMsg2, "Time Over!");
		SetStatus(Status::GameOver);
		return;
	}
}

void SceneDev2::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev2::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev2::OnChop(Sides side)
{
	

	/*Sides branchSide = tree->Chop(side);
	if (player->GetSide() == branchSide)
	{
		sfxDeath.play();

		player->OnDie();
		SetCenterMessage("You Die!");
		SetStatus(Status::GameOver);
	}
	else
	{
		timer += 1.f;
	}*/
}