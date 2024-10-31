#pragma once

class ViewTest : public Singleton<ViewTest>
{
	friend class Singleton<ViewTest>;
protected:
	sf::View* views[2];

	float time[2] = {};
	float duration[2] = {};
	float amplitude[2] = {};
	float period[2] = {};

	sf::Vector2f center[2];
	sf::Vector2f size[2];

	SceneIds gameMode = SceneIds::Dev1;

	ViewTest() = default;
	virtual ~ViewTest() = default;

	ViewTest(const ViewTest&) = delete;
	ViewTest& operator=(const ViewTest&) = delete;

public:

	void Init();
	void Release();

	void Update(float dt);

	void Reset();

	void RunShake(int idx, float duration, float amplitude, float period);

	sf::View* GetView(int idx) const;
	void SetViewRect(SceneIds id);
};

