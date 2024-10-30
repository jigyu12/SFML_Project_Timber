#pragma once
#include "SpriteGo.h"

class Branch : public SpriteGo
{
protected:
	Sides side = Sides::None;

public:
	Branch(const std::string& texId, const std::string& name = "");
	~Branch() = default;


	void SetSide(Sides side);
	Sides GetSide() const { return side; }

};

