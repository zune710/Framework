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

	rcPoint2 = { 145, 145, 155, 155 };
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
		
		rcPoint2 = { 145, 145, 155, 155 };

		while (rcPoint2.left < 1000)
		{

			rcPoint2.left += value;
			rcPoint2.right += value;
			InvalidateRect(g_hWnd, NULL, true);
		}

	}
}

void MainUpdate::Render()
{
	//Rectangle(m_hdc, 0, 0, 1280, 720);
	
	/*Rectangle(m_hdc, 
		rcPoint.left, 
		rcPoint.top, 
		rcPoint.right, 
		rcPoint.bottom);*/

	Ellipse(m_hdc,
		rcPoint2.left,
		rcPoint2.top,
		rcPoint2.right,
		rcPoint2.bottom);
}

void MainUpdate::Destroy()
{

}
