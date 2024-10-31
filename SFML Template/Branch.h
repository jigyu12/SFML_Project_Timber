#pragma once
#include "SpriteGo.h"

class Branch : public SpriteGo
{
public:
	enum class BranchStatus
	{
		Normal,
		Apple,
		GoldenApple,
		BeeHive,
		BadApple,
	};

protected:
	
	Sides side = Sides::None;
	BranchStatus eStatus = BranchStatus::Normal;
	
	sf::Vector2f localOriginApple = { -115.f, -35.f };
	sf::Vector2f localOriginGoldenApple = { -115.f, -35.f };
	sf::Vector2f localOriginBeehive = { -115.f, -35.f };

	sf::Sprite sprApple;
	sf::Sprite sprGoldenApple;
	sf::Sprite sprBeehive;
	SpriteGo* spgApple;
	SpriteGo* spgGoldenApple;
	SpriteGo* spgBeehive;
	std::string appleTextureId = "graphics/apple.png";
	std::string goldenAppleTextureId = "graphics/goldenapple.png";
	std::string beehiveeTextureId = "graphics/beehive.png";

public:
	Branch(const std::string& texId, const std::string& name = "");
	~Branch() = default;

	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(const sf::Vector2f& origin) override;

	void SetSide(Sides side);
	Sides GetSide() const { return side; }

	void RandStatus();
	BranchStatus GetStatus() const;
};

