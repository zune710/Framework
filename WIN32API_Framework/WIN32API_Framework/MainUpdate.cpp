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
}

void MainUpdate::Update()
{
	GetSingle(InputManager)->CheckKey();
	GetSingle(SceneManager)->Update();
}

void MainUpdate::Render()
{
	//Rectangle(m_hdc, 0, 0, WIDTH, HEIGHT);

	GetSingle(SceneManager)->Render(m_hdc);
}

void MainUpdate::Destroy()
{
	
}
