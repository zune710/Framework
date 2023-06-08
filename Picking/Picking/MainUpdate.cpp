#include "MainUpdate.h"
#include "SceneManager.h"
#include "Stage.h"

MainUpdate::MainUpdate() : m_hdc(NULL), stage(nullptr)
{
}

MainUpdate::~MainUpdate()
{
	Destroy();
}

void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);
	
	srand((unsigned int)GetTickCount64());

	GetSingle(SceneManager)->SetScene(STAGE);
}

void MainUpdate::Update()
{
	GetSingle(SceneManager)->Update();
}

void MainUpdate::Render()
{
	//Rectangle(m_hdc, 0, 0, 1500, 1000);
	GetSingle(SceneManager)->Render(m_hdc);
}

void MainUpdate::Destroy()
{

}
