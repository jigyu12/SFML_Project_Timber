#include "stdafx.h"
#include "Branch.h"

Branch::Branch(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	spgApple = new SpriteGo(appleTextureId, "Apple");
	spgGoldenApple = new SpriteGo(goldenAppleTextureId, "GoldenApple");
	spgBeehive = new SpriteGo(beehiveeTextureId, "Beehive");
}

void Branch::Reset()
{
	SpriteGo::Reset();

	spgApple->Reset();
	spgGoldenApple->Reset();
	spgBeehive->Reset();

	SetSide(side);
	eStatus = BranchStatus::Normal;
}

void Branch::Draw(sf::RenderWindow& window)
{
	switch (eStatus)
	{
	case Branch::BranchStatus::Apple:
		spgApple->Draw(window);
		break;
	case Branch::BranchStatus::GoldenApple:
		spgGoldenApple->Draw(window);
		break;
	case Branch::BranchStatus::BeeHive:
		spgBeehive->Draw(window);
		break;
	default:
		break;
	}
	SpriteGo::Draw(window);
}

void Branch::Release()
{
}

void Branch::SetOrigin(const sf::Vector2f& newOrigin)
{
	SpriteGo::SetOrigin(newOrigin);
	spgApple->SetOrigin(origin + localOriginApple);
	spgGoldenApple->SetOrigin(origin + localOriginGoldenApple);
	spgBeehive->SetOrigin(origin + localOriginBeehive);
}

void Branch::SetPosition(const sf::Vector2f& pos)
{
	SpriteGo::SetPosition(pos);
	spgApple->SetPosition(pos);
	spgGoldenApple->SetPosition(pos);
	spgBeehive->SetPosition(pos);
}

void Branch::SetSide(Sides side)
{
	this->side = side;
	switch (this->side)
	{
	case Sides::Left:
		SetActive(true);
		SetScale({ -1.f, 1.f });
		spgApple->SetScale({ -1.f,1.f });
		spgGoldenApple->SetScale({ -1.f,1.f });
		spgBeehive->SetScale({ -1.f,1.f });
		break;
	case Sides::Right:
		SetActive(true);
		SetScale({ 1.f, 1.f });
		spgApple->SetScale({ 1.f,1.f });
		spgGoldenApple->SetScale({ 1.f,1.f });
		spgBeehive->SetScale({ 1.f,1.f });
		break;
	default:
		SetActive(false);
		break;
	}
}

void Branch::RandStatus()
{
	float prob = Utils::RandomValue();
	if (prob < 0.03f)
	{
		eStatus = BranchStatus::GoldenApple;
	}
	else if (prob < 0.08f)
	{
		eStatus = BranchStatus::BeeHive;
	}
	else if (prob < 0.18f)
	{
		eStatus = BranchStatus::Apple;
	}
	else
	{
		eStatus = BranchStatus::Normal;
	}
	active = true;
}

Branch::BranchStatus Branch::GetStatus() const
{
	return eStatus;
}
