#pragma once
#include "Include.h"

class Scene;
class SceneManager
{
public:
	Single(SceneManager)

private:
	Scene* SceneState;
public:
	void SetScene(SCENEID _State);
	void Update();
	void Render(HDC hdc);
	void Destroy();

private:
	SceneManager();
public:
	~SceneManager();
};

