#include "MainUpdate.h"
#include "InputManager.h"
#include "SceneManager.h"

MainUpdate::MainUpdate() : m_hdc(NULL)
{
}

MainUpdate::~MainUpdate()
{
}


void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);

	SceneManager::GetInstance()->SetScene(LOGO);
}

void MainUpdate::Update()
{
	InputManager::GetInstance()->CheckKey();
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
