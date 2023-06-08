#include "SceneManager.h"

//#include "Logo.h"
#include "Menu.h"
#include "Stage.h"

SceneManager::SceneManager() : SceneState(nullptr)
{
}

SceneManager::~SceneManager()
{
	Destroy();
}

void SceneManager::SetScene(SCENEID _State)
{
	if (SceneState != nullptr)
		::Safe_Release(SceneState);  // ::붙여서 인라인 함수임을 보여준다.

	switch (_State)
	{
	/*
	case LOGO:
		SceneState = new Logo;
		break;
	*/

	case MENU:
		SceneState = new Menu;
		break;

	case STAGE:
		SceneState = new Stage;
		break;
	}

	SceneState->Start();
}

void SceneManager::Update()
{
	SceneState->Update();
}

void SceneManager::Render(HDC hdc)
{
	SceneState->Render(hdc);
}

void SceneManager::Destroy()
{
	::Safe_Release(SceneState);
}
