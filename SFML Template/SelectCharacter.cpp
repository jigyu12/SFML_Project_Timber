#include "stdafx.h"
#include "SelectCharacter.h"


SelectCharacter::SelectCharacter()
	:Scene(id)
{
}



void SelectCharacter::Init()
{
	gameMessage = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "game"));
	player =AddGo(new SpriteGo("graphics/player.png"));
	player2 =AddGo(new SpriteGo("graphics/player2.png"));
	Scene::Init();

	gameMessage->text.setCharacterSize(140);
	gameMessage->text.setFillColor(sf::Color::Blue);
	SetGameMessage("Select Player1\'s Sprite\n Press [1] or [2]");
	gameMessage->SetPosition({ 1920.f / 2,1080.f / 4 });

	player->SetPosition({ 1920.f / 4,1080.f / 2 });
	player->SetOrigin(Origins::MC);
	player2->SetPosition({ 1920.f- 1920.f/4,1080.f- 1080.f / 2 });
	player2->SetOrigin(Origins::MC);

}

void SelectCharacter::Enter()
{
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SelectCharacter::Exit()
{
	Scene::Exit();
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SelectCharacter::SetGameMessage(const std::string& msg)
{
	gameMessage->text.setString(msg);
	gameMessage->SetOrigin(Origins::MC);
}

void SelectCharacter::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.player1sprite = PlayerSelect::Player1;

		SCENE_MGR.ChangeScene(SCENE_MGR.GetGameMode());
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.player1sprite = PlayerSelect::Player2;

		SCENE_MGR.ChangeScene(SCENE_MGR.GetGameMode());
	}
}

void SelectCharacter::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
