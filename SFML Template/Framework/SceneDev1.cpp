#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

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
	bee = AddGo(new SpriteGo("graphics/bee.png", "bee"));

	TEXTURE_MGR.Load("graphics/apple.png");
	TEXTURE_MGR.Load("graphics/goldenapple.png");
	TEXTURE_MGR.Load("graphics/beehive.png");
	TEXTURE_MGR.Load("graphics/fire.png");

	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");

	tree = AddGo(new Tree("Tree"));
	
	player1 = AddGo(new Player(PlayerSelect::Player1, "Player"));
	player2 = AddGo(new Player(PlayerSelect::Player2, "Player"));


	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message"));
	centerMsg->sortingLayer = SortingLayers::UI;

	uiScore = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score"));
	uiTimer = AddGo(new UiTimebar("Ui Timer"));

	Scene::Init();

	tree->SetPosition({ 1920.f / 2, 1080.f - 200.f });
	player1->SetPosition({ 1920.f / 2, 1080.f - 200.f });
	player2->SetPosition({ 1920.f / 2, 1080.f - 200.f });
	player1->SetActive(false);
	player2->SetActive(false);

	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f });

	uiScore->text.setCharacterSize(75);
	uiScore->text.setFillColor(sf::Color::White);
	uiScore->SetPosition({ 30.f, 30.f });

	uiTimer->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer->SetOrigin(Origins::ML);
	uiTimer->SetPosition({ 1920.f / 2.f - 250.f, 1080.f - 100.f });
}

void SceneDev1::Enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/fire.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/bee.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load("sound/chop.wav");
	SOUNDBUFFER_MGR.Load("sound/eat.mp3");
	SOUNDBUFFER_MGR.Load("sound/star.mp3");
	SOUNDBUFFER_MGR.Load("sound/bee.mp3");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);

	if (SCENE_MGR.player1Select == 1)
	{
		player1->SetActive(true);
		player = player1;
	}
	if (SCENE_MGR.player1Select == 2)
	{
		player2->SetActive(true);
		player = player2;
	}

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));
	sfxBee.setBuffer(SOUNDBUFFER_MGR.Get(sbIdBee));
	bee->SetOrigin(Origins::MC);
	bee->sortingLayer = SortingLayers::Foreground;
	bee->sortingOrder = 10;

	player->SetSceneGame(this);

	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneDev1::Exit()
{
	std::cout << "SceneDev1::Exit()" << std::endl;

	player->SetSceneGame(nullptr);
	tree->ClearEffectLog();

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/fire.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload(sbIdDeath);
	SOUNDBUFFER_MGR.Unload(sbIdTimeOut);
	SOUNDBUFFER_MGR.Unload("sound/eat.mp3");
	SOUNDBUFFER_MGR.Unload("sound/star.mp3");
	SOUNDBUFFER_MGR.Unload("sound/bee.mp3");

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneDev1::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneDev1::Status::Game:
		UpdateGame(dt);
		break;
	case SceneDev1::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneDev1::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev1::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SceneDev1::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}

void SceneDev1::SetScore(int score)
{
	this->score = score;
	uiScore->SetScore(this->score);
}

void SceneDev1::AddScore(int score)
{
	this->score += score;
	uiScore->SetScore(this->score);
}

void SceneDev1::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneDev1::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		score = 0;
		timer = gameTime;
		SetScore(score);
		uiTimer->SetValue(1.f);
		break;
	case SceneDev1::Status::Game:
		SCENE_MGR.SetIsGaming(true);
		if (prevStatus == Status::GameOver)
		{
			score = 0;
			timer = gameTime;

			SetScore(score);
			uiTimer->SetValue(1.f);

			player->Reset();
			tree->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case SceneDev1::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);

		SCENE_MGR.SetIsGaming(false);
		break;
	case SceneDev1::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");

		SCENE_MGR.SetIsGaming(false);
		break;
	}
}

void SceneDev1::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}


	timer = player->GetLife();
	uiTimer->SetValue(timer / gameTime);

	bee->SetScale(bee->GetScale() * (1.f + dt * 3.f));
	if (bee->GetScale().x > 30.f)
	{
		bee->SetActive(false);
	}
}

void SceneDev1::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::MainTitle);
	}
}

void SceneDev1::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::OnChop(Sides side)
{
	Sides branchSide = tree->Chop(side);
	BranchStatus branchStat = tree->GetLastBranchStatus();
	player->Chopped(branchSide, branchStat);

}

void SceneDev1::OnDie(bool isTimeOver)
{
	if (isTimeOver)
	{
		SetCenterMessage("           Time Over!\nPress Enter to MainTitle");
		SetStatus(Status::GameOver);
		sfxTimeOut.play();
		return;
	}
	SetCenterMessage("           You Die!\nPress Enter to MainTitle");
	SetStatus(Status::GameOver);
	sfxDeath.play();
}

void SceneDev1::OnBeehive(Sides side)
{
	sf::Vector2f pos = tree->GetPosition();
	if (side == Sides::Left)
	{
		//pos += rightBranches.front()->GetOrigin();
		pos += {-290.f, -130.f};
	}
	else
	{
		//pos -= rightBranches.front()->GetOrigin();
		pos += {290.f, -130.f};
	}
	bee->SetPosition(pos);
	bee->SetScale({ 0.05f,0.05f });
	bee->SetActive(true);
	sfxBee.play();
}
