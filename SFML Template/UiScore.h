#pragma once
#include "TextGo.h"
class UiScore : public TextGo
{
protected:
	std::string textFormat = "SCORE: ";
	int score = 0;

public:
	UiScore(const std::string& fontId, const std::string& name = "");
	~UiScore() = default;

	void Reset();
	void SetScore(int score);
};

