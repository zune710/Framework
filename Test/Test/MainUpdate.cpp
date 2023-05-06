#include "MainUpdate.h"
#include "SceneManager.h"

MainUpdate::MainUpdate()
{
}

MainUpdate::~MainUpdate()
{
	Destroy();
}

void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);

	SceneManager::GetInstance()->SetScene(LOGO);
}

void MainUpdate::Update()
{
	SceneManager::GetInstance()->Update();
}

void MainUpdate::Render()
{
	Rectangle(m_hdc, 0, 0, WIDTH, HEIGHT);
	
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Destroy()
{

}
