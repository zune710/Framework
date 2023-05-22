#include "MainUpdate.h"
#include "SceneManager.h"
#include "InputManager.h"


MainUpdate::MainUpdate() : m_hdc(NULL)
{

}

MainUpdate::~MainUpdate()
{
	Destroy();
}

void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);
	
	GetSingle(SceneManager)->SetScene(LOGO);
	//SceneManager::GetInstance()->SetScene(LOGO);
}

void MainUpdate::Update()
{
	GetSingle(InputManager)->CheckKey();
	//InputManager::GetInstance()->CheckKey(); // 순서 먼저
	
	GetSingle(SceneManager)->Update();
	//SceneManager::GetInstance()->Update();
}

void MainUpdate::Render()
{
	Rectangle(m_hdc, 0, 0, WIDTH, HEIGHT);

	GetSingle(SceneManager)->Render(m_hdc);
	//SceneManager::GetInstance()->Render(m_hdc);

}

void MainUpdate::Destroy()
{
	
}
