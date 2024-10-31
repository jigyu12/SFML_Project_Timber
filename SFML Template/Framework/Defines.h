#pragma once

enum class SortingLayers
{
	Background,
	Foreground,
	UI,
	Default,
};

enum class SceneIds
{
	None = -1,
	MainTitle,
	SelectGameMode,
	PraticePage,
	Dev1,
	Dev2,
	Count,
};

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
};

enum class BranchStatus
{
	Normal,
	Apple,
	GoldenApple,
	BeeHive,
	BadApple,
};

enum class PlayerSelect
{
	Player1,
	Player2,
	None,
};