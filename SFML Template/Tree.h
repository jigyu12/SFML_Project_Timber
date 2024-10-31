#pragma once
#include "GameObject.h"
#include "EffectLog.h"
#include "Branch.h"

class Tree : public GameObject
{
protected:
	sf::Sound sfxBee;
	sf::Sprite tree;
	std::list<Branch*> leftBranches;
	std::list<Branch*> rightBranches;

	int branchCount = 6;
	std::string treeTexId = "graphics/tree.png";
	std::string branchTexId = "graphics/branch.png";

	BranchStatus lastBranchStat = BranchStatus::Normal;

	float brachOffsetY = 150.f;

	ObjectPool<EffectLog> effectLogPool;
	std::list<EffectLog*> logEffects;

public:
	Tree(const std::string& name = "");
	~Tree();

	Sides RandomSide() const;
	Sides Chop(Sides side);

	void UpdateBranchPos();

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;

	void ClearEffectLog();

	BranchStatus GetLastBranchStatus() const;
};

