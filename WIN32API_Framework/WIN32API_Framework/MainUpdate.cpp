#include "MainUpdate.h"

MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{

}

void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);

	rcPoint.left = 100;
	rcPoint.top = 100;

	rcPoint.right = 200;
	rcPoint.bottom = 200;
}

void MainUpdate::Update()
{
	int value = 1;
	
	if (GetAsyncKeyState(VK_UP))  // Virtual Key
	{
		rcPoint.top -= value;
		rcPoint.bottom -= value;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		rcPoint.top += value;
		rcPoint.bottom += value;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		rcPoint.left -= value;
		rcPoint.right -= value;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		rcPoint.left += value;
		rcPoint.right += value;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{

	}
}

void MainUpdate::Render()
{
	//Rectangle(m_hdc, 0, 0, 1280, 720);
	
	Rectangle(m_hdc, 
		rcPoint.left, 
		rcPoint.top, 
		rcPoint.right, 
		rcPoint.bottom);
}

void MainUpdate::Destroy()
{

}
