#include "stdafx.h"
#include "ViewTest.h"

void ViewTest::Init()
{
	for (int i = 0;i < 2;++i)
	{
		sf::View* test = new sf::View();
		views[i] = test;
	}
}

void ViewTest::Release()
{
	for (auto& view : views)
	{
		delete view;
	}
}

void ViewTest::Update(float dt)
{
	time[0] += dt;
	time[1] += dt;

	for (int i = 0;i < sizeof(views) / sizeof(views[0]);++i)
	{
		sf::Vector2f viewcenter = views[i]->getCenter();
		if (time[i] < duration[i])
		{
			viewcenter.x = center[i].x + amplitude[i] * sinf(time[i] * 2.f * Utils::PI / period[i]);
		}
		else
		{
			if (gameMode == SceneIds::Dev1)
			{
				viewcenter.x = 1920.f * 0.5f;
			}
			if (gameMode == SceneIds::Dev2)
			{
				viewcenter.x = 1920.f * (0.25f + 0.5f * i);
			}
		}
		views[i]->setCenter(viewcenter);
	}
}

void ViewTest::Reset()
{
	for (int i = 0;i < sizeof(views) / sizeof(views[0]);++i)
	{
		time[i] = 0.f;
		duration[i] = 0.f;
		amplitude[i] = 0.f;
		period[i] = 0.f;
	}
}

void ViewTest::RunShake(int idx, float duration, float amplitude, float period)
{
	time[idx] = 0.f;
	this->duration[idx] = duration;
	this->amplitude[idx] = amplitude;
	this->period[idx] = period;
}

sf::View* ViewTest::GetView(int idx) const
{
	return views[idx];
}

void ViewTest::SetViewRect(SceneIds gamemode)
{
	Reset();
	gameMode = gamemode;
	if (gameMode == SceneIds::Dev1)
	{
		center[0] = { 1920.f * 0.5f,1080.f * 0.5f };
		views[0]->setCenter({ 1920.f * 0.5f,1080.f * 0.5f });
		views[0]->setSize({ 1920.f,1080.f });
		views[0]->setViewport({ 0.f,0.0f,1.f,1.f });
	}
	if (gameMode == SceneIds::Dev2)
	{
		center[0] = { 1920.f * 0.25f,1080.f * 0.5f };
		views[0]->setCenter({ 1920.f * 0.25f,1080.f * 0.5f });
		views[0]->setSize({ 1920.f * 0.5f,1080.f });
		views[0]->setViewport({ 0.f,0.0f,0.5f,1.f });

		center[1] = { 1920.f * 0.75f,1080.f * 0.5f };
		views[1]->setCenter({ 1920.f * 0.75f,1080.f * 0.5f });
		views[1]->setSize({ 1920.f * 0.5f,1080.f });
		views[1]->setViewport({ 0.5f,0.f,0.5f,1.f });
	}
}
