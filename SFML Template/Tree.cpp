#include "stdafx.h"
#include "Tree.h"
#include "EffectLog.h"
#include "Scene.h"

Tree::Tree(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;
}

Tree::~Tree()
{
	Release();
}

void Tree::Init()
{
	Release();

	tree.setTexture(TEXTURE_MGR.Get(treeTexId), true);
	Utils::SetOrigin(tree, Origins::BC);

	sf::Vector2f orginBranch;
	orginBranch.x = tree.getLocalBounds().width * -0.5f;
	sf::Texture& branchTex = TEXTURE_MGR.Get(branchTexId);
	orginBranch.y = branchTex.getSize().y * 0.5f;

	for (int i = 0; i < branchCount; ++i)
	{
		Branch* branch = new Branch(branchTexId);
		branch->SetOrigin(orginBranch);
		branch->Init();
		branch->SetSide(Sides::Left);
		leftBranches.push_back(branch);
		branch = new Branch(branchTexId);
		branch->SetOrigin(orginBranch);
		branch->Init();
		branch->SetSide(Sides::Right);
		rightBranches.push_back(branch);
	}
}

void Tree::Release()
{
	for (auto logEffect : logEffects)
	{
		effectLogPool.Return(logEffect);
		SCENE_MGR.GetCurrentScene()->RemoveGo(logEffect);
	}
	logEffects.clear();

	for (auto branch : leftBranches)
	{
		branch->Release();
		delete branch;
	}
	leftBranches.clear();
	for (auto branch : rightBranches)
	{
		branch->Release();
		delete branch;
	}
	rightBranches.clear();
}


void Tree::Reset()
{
	tree.setTexture(TEXTURE_MGR.Get(treeTexId), true);
	bee.setTexture(TEXTURE_MGR.Get(beeTexId), true);

	auto leftbranch = leftBranches.begin();
	auto rightbranch = rightBranches.begin();

	while (leftbranch != leftBranches.end() || rightbranch != rightBranches.end())
	{
		(*leftbranch)->Reset();
		(*leftbranch)->RandStatus();
		(*rightbranch)->Reset();
		(*rightbranch)->RandStatus();

		if (((*leftbranch)->GetStatus() == BranchStatus::Normal || (*leftbranch)->GetStatus() == BranchStatus::BeeHive)
			&& (((*rightbranch)->GetStatus() == BranchStatus::Normal) || (*rightbranch)->GetStatus() == BranchStatus::BeeHive))
		{
			Utils::RandomRange(0, 1) == 0 ? (*leftbranch)->SetActive(false) : (*rightbranch)->SetActive(false);
		}

		++leftbranch;
		++rightbranch;
	}

	auto lastBranch = leftBranches.front();
	lastBranch->SetActive(false);
	lastBranch = rightBranches.front();
	lastBranch->SetActive(false);
	UpdateBranchPos();
}

void Tree::Update(float dt)
{
	for (auto branch : leftBranches)
	{
		branch->Update(dt);
	}
	for (auto branch : rightBranches)
	{
		branch->Update(dt);
	}

	auto it = logEffects.begin();
	while (it != logEffects.end())
	{
		auto logEffect = *it;
		if (!logEffect->IsActive())
		{
			effectLogPool.Return(logEffect);
			SCENE_MGR.GetCurrentScene()->RemoveGo(logEffect);
			it = logEffects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	window.draw(tree);
	for (auto branch : leftBranches)
	{
		if (branch->IsActive())
		{
			branch->Draw(window);
		}
	}
	for (auto branch : rightBranches)
	{
		if (branch->IsActive())
		{
			branch->Draw(window);
		}
	}
}

void Tree::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	tree.setPosition(position);
	UpdateBranchPos();
}

void Tree::ClearEffectLog()
{
	for (auto log : logEffects)
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(log);
		effectLogPool.Return(log);
	}
	logEffects.clear();
}

BranchStatus Tree::GetLastBranchStatus() const
{
	return lastBranchStat;
}

Sides Tree::RandomSide() const
{
	return Sides();
}

Sides Tree::Chop(Sides side)
{
	Branch* leftTemp = leftBranches.front();
	Branch* rightTemp = rightBranches.front();
	Sides sides = Sides::Left;

	if (side != Sides::None)
	{
		EffectLog* effect = effectLogPool.Take();
		SCENE_MGR.GetCurrentScene()->AddGo(effect);
		effect->SetOrigin(Origins::BC);
		effect->SetPosition(position);
		effect->Fire({ side == Sides::Right ? -1000.f : 1000.f, -1000.f });
		logEffects.push_back(effect);
	}

	leftBranches.pop_front();
	leftTemp->RandStatus();
	leftBranches.push_back(leftTemp);
	rightBranches.pop_front();
	rightTemp->RandStatus();
	rightBranches.push_back(rightTemp);
	if ((leftTemp->GetStatus() == BranchStatus::Normal || leftTemp->GetStatus() == BranchStatus::BeeHive)
		&& (rightTemp->GetStatus() == BranchStatus::Normal || rightTemp->GetStatus() == BranchStatus::BeeHive))
	{
		Utils::RandomRange(0, 1) == 0 ? leftTemp->SetActive(false) : rightTemp->SetActive(false);
	}

	UpdateBranchPos();
	leftTemp = leftBranches.front();
	rightTemp = rightBranches.front();
	if (side == Sides::Left)
	{
		lastBranchStat = leftTemp->GetStatus();
		sides = leftTemp->IsActive() ? Sides::Left : Sides::Right;
	}
	else if (side == Sides::Right)
	{
		lastBranchStat = rightTemp->GetStatus();
		sides = rightTemp->IsActive() ? Sides::Right : Sides::Left;
	}
	return sides;
}

void Tree::ToBee(Sides side)
{
	sf::Vector2f pos;
}

void Tree::UpdateBranchPos()
{
	sf::Vector2f pos = position;
	for (auto branch : leftBranches)
	{
		pos.y -= brachOffsetY;
		branch->SetPosition(pos);
	}
	pos = position;
	for (auto branch : rightBranches)
	{
		pos.y -= brachOffsetY;
		branch->SetPosition(pos);
	}
}

