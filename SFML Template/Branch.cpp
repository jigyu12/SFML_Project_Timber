#include "stdafx.h"
#include "Branch.h"

Branch::Branch(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}	

void Branch::SetSide(Sides side)
{
	this->side = side;
	switch (this->side)
	{
	case Sides::Left:
		SetActive(true);
		SetScale({ -1.f, 1.f });
		break;
	case Sides::Right:
		SetActive(true);
		SetScale({ 1.f, 1.f });
		break;
	default:
		SetActive(false);
		break;
	}
}
