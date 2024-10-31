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
	bee1 = AddGo(new SpriteGo("graphics/bee.png", "b1"));
	bee2 = AddGo(new SpriteGo("graphics/bee.png", "b2"));

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

	tree1 = AddGo(new Tree("Tree1"));
	tree2 = AddGo(new Tree("Tree2"));
	player1_1 = AddGo(new Player(PlayerSelect::Player1, "Player1"));
	player2_1 = AddGo(new Player(PlayerSelect::Player2, "Player2"));
	player1_2 = AddGo(new Player(PlayerSelect::Player2, "Player1"));
	player2_2 = AddGo(new Player(PlayerSelect::Player1, "Player2"));

	centerMsg1 = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message1"));
	centerMsg1->sortingLayer = SortingLayers::UI;

	centerMsg2 = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message2"));
	centerMsg2->sortingLayer = SortingLayers::UI;

	uiTimer1 = AddGo(new UiTimebar("Ui Timer1"));
	uiTimer2 = AddGo(new UiTimebar("Ui Timer2"));

	Scene::Init();

	tree1->SetPosition({ 1920.f * 0.25f, 1080.f - 200.f });
	player1_1->SetPosition({ 1920.f * 0.25f, 1080.f - 200.f });
	player1_2->SetPosition({ 1920.f * 0.25f, 1080.f - 200.f });
	player1_1->SetActive(false);
	player1_2->SetActive(false);

	tree2->SetPosition({ 1920.f * 0.75f, 1080.f - 200.f });
	player2_1->SetPosition({ 1920.f * 0.75f, 1080.f - 200.f });
	player2_2->SetPosition({ 1920.f * 0.75f, 1080.f - 200.f });
	player2_1->SetActive(false);
	player2_2->SetActive(false);

	centerMsg1->text.setCharacterSize(50);
	centerMsg1->text.setFillColor(sf::Color::White);
	centerMsg1->SetPosition({ 1920.f / 2.f / 2.f, 1080.f / 2.f });

	centerMsg2->text.setCharacterSize(50);
	centerMsg2->text.setFillColor(sf::Color::White);
	centerMsg2->SetPosition({ 1920.f / 2.f / 2.f * 3, 1080.f / 2.f });

	uiTimer1->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer1->SetOrigin(Origins::ML);
	uiTimer1->SetPosition({ 1920.f * 0.25f - 250.f, 1080.f - 100.f });

	uiTimer2->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer2->SetOrigin(Origins::ML);
	uiTimer2->SetPosition({ 1920.f * 0.75f - 250.f, 1080.f - 100.f });
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
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/rip.png");
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
		player1_1->SetActive(true);
		player2_1->SetActive(true);
		player1_2->SetActive(false);
		player2_2->SetActive(false);
		player1 = player1_1;
		player2 = player2_1;
		
	}
	if (SCENE_MGR.player1Select == 2)
	{
		player1_1->SetActive(false);
		player2_1->SetActive(false);
		player1_2->SetActive(true);
		player2_2->SetActive(true);
		player1 = player1_2;
		player2 = player2_2;
	}
	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));

	player1->SetSceneGame(this);
	player2->SetSceneGame(this);
	bee1->SetOrigin(Origins::MC);
	bee1->sortingLayer = SortingLayers::Foreground;
	bee1->sortingOrder = 10;
	bee2->SetOrigin(Origins::MC);
	bee2->sortingLayer = SortingLayers::Foreground;
	bee2->sortingOrder = 10;

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
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/eat.mp3");
	SOUNDBUFFER_MGR.Unload("sound/star.mp3");
	SOUNDBUFFER_MGR.Unload("sound/bee.mp3");
	SOUNDBUFFER_MGR.Unload(sbIdDeath);
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");

}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

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
		SCENE_MGR.SetIsGaming(true);
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
		if (!isPlayer1GameOver)
			SetVisibleCenterMessage(centerMsg1, false);
		else if (!isPlayer2GameOver)
			SetVisibleCenterMessage(centerMsg2, false);
		break;
	case SceneDev2::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(centerMsg1, true);
		SetVisibleCenterMessage(centerMsg2, true);

		SCENE_MGR.SetIsGaming(false);
		break;
	case SceneDev2::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(centerMsg1, true);
		SetVisibleCenterMessage(centerMsg2, true);
		SetCenterMessage(centerMsg1, "PAUSE! ESC TO RESUME!");
		SetCenterMessage(centerMsg2, "PAUSE! ESC TO RESUME!");

		SCENE_MGR.SetIsGaming(false);
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

	timer1 = player1->GetLife();
	timer2 = player2->GetLife();
	uiTimer1->SetValue(timer1 / gameTime);
	uiTimer2->SetValue(timer2 / gameTime);

	if (bee1->IsActive())
	{
		bee1->SetScale(bee1->GetScale() * (1.f + dt * 3.f));
		if (bee1->GetScale().x > 30.f)
		{
			bee1->SetActive(false);
		}
	}
	if (bee2->IsActive())
	{
		bee2->SetScale(bee2->GetScale() * (1.f + dt * 3.f));
		if (bee2->GetScale().x > 30.f)
		{
			bee2->SetActive(false);
		}
	}
}

void SceneDev2::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::MainTitle);
	}
}

void SceneDev2::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev2::OnChop(Sides side, Player* player)
{
	if (player == player1)
	{
		Sides branchSide = tree1->Chop(side);
		BranchStatus branchStat = tree1->GetLastBranchStatus();
		player1->Chopped(branchSide, branchStat);
	}
	if (player == player2)
	{
		Sides branchSide = tree2->Chop(side);
		BranchStatus branchStat = tree2->GetLastBranchStatus();
		player2->Chopped(branchSide, branchStat);
	}
}

void SceneDev2::OnDie(bool isTimeOver, Player* player)
{
	if (isTimeOver)
	{
		if (player == player1)
		{
			SetCenterMessage(centerMsg1, "           Time Over!\nPress Enter to MainTitle");
			isPlayer1GameOver = true;
			sfxTimeOut.play();
		}
		else if (player == player2)
		{
			SetCenterMessage(centerMsg2, "           Time Over!\nPress Enter to MainTitle");
			isPlayer2GameOver = true;
			sfxTimeOut.play();
		}

		if (isPlayer1GameOver && isPlayer2GameOver)
		{
			SetStatus(Status::GameOver);
		}
		return;
	}

	if (player == player1)
	{
		SetCenterMessage(centerMsg1, "           You Die!\nPress Enter to MainTitle");
		isPlayer1GameOver = true;
		sfxDeath.play();
	}
	else if (player == player2)
	{
		SetCenterMessage(centerMsg2, "           You Die!\nPress Enter to MainTitle");
		isPlayer2GameOver = true;
		sfxDeath.play();
	}

	if (isPlayer1GameOver && isPlayer2GameOver)
	{
		SetStatus(Status::GameOver);
	}
}

void SceneDev2::OnBeehive(Sides side, Player* player)
{
	sf::Vector2f pos;
	if (player == player1)
	{
		pos = tree1->GetPosition();
		if (side == Sides::Left)
		{
			pos += {-290.f, -130.f};
		}
		else
		{
			pos += {290.f, -130.f};
		}
		bee1->SetPosition(pos);
		bee1->SetScale({ 0.05f,0.05f });
		bee1->SetActive(true);
	}
	if (player == player2)
	{
		pos = tree2->GetPosition();
		if (side == Sides::Left)
		{
			pos += {-290.f, -130.f};
		}
		else
		{
			pos += {290.f, -130.f};
		}
		bee2->SetPosition(pos);
		bee2->SetScale({ 0.05f,0.05f });
		bee2->SetActive(true);
	}

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
	bee1->SetPosition(pos);
	bee1->SetScale({ 0.05f,0.05f });
	bee1->SetActive(true);
	sfxBee.play();
}
