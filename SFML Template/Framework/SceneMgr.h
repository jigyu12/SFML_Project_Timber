#pragma once

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::MainTitle;
	SceneIds currentScene;

	SceneIds gameMode = SceneIds::None;

	SceneIds nextScene = SceneIds::None;

	bool isGaming = false;
	
	SceneMgr() = default;
	virtual ~SceneMgr() = default;

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;

	void OnPreDraw();
	void OnPostDraw();

public:

	int player1Select;
	int player2Select;

	void Init();
	void Release();

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene; }
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void LateUpdate(float dt);

	void Draw(sf::RenderWindow& window);

	void SetGameMode(const SceneIds& mode) { gameMode = mode; }
	SceneIds GetGameMode() const { return gameMode; }

	void SetIsGaming(const bool gaming) { isGaming = gaming; }
	bool GetIsGaming() const { return isGaming; }
};


#define SCENE_MGR (SceneMgr::Instance())

