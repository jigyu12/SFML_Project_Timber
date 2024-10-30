#include "stdafx.h"
#include "UiScore.h"

UiScore::UiScore(const std::string& fontId, const std::string& name)
	: TextGo(fontId, name)
{
	sortingLayer = SortingLayers::UI;
}

void UiScore::Reset()
{
	TextGo::Reset();
	SetScore(0);
}

void UiScore::SetScore(int score)
{
	this->score = score;
	text.setString(textFormat + std::to_string(this->score));
	SetOrigin(originPreset);
}


