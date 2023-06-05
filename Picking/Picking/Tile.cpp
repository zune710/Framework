#include "Tile.h"
#include "Bitmap.h"

Tile::Tile() : check(0)
{
}

Tile::~Tile()
{
}

void Tile::Start()
{
	check = 0;

	position = Vector3(100.0f, 100.0f);
	scale = Vector3(32.0f, 32.0f);

	cntX = 1;
	cntY = 0;
	Key = "Tile";
}

void Tile::Update()
{
	POINT ptMouse;

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	/*
	if (check)  // Rectangle 충돌
	{ 
		if (position.x - (scale.x * 0.5f) < ptMouse.x &&
			position.y - (scale.y * 0.5f) < ptMouse.y &&
			ptMouse.x < position.x + (scale.x * 0.5f) &&
			ptMouse.y < position.y + (scale.y * 0.5f))
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				check = !check;
				Sleep(80);
			}
		}
	}
	else  // Circle 충돌
	{
		float fx = position.x - ptMouse.x;
		float fy = position.y - ptMouse.y;

		float value = (fx * fx) + (fy * fy);
		float distance = (float)sqrt((double)value);

		if (distance < scale.x * 0.5f)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				check = !check;
				Sleep(80);
			}
		}
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		check = !check;
		Sleep(80);
	}
	*/

	if (position.x - (scale.x * 0.5f) < ptMouse.x &&
		position.y - (scale.y * 0.5f) < ptMouse.y &&
		ptMouse.x < position.x + (scale.x * 0.5f) &&
		ptMouse.y < position.y + (scale.y * 0.5f))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			// 두 가지 색만 사용
			check = !check;

			if (check)  // BLUE
			{
				cntX = 1;
				cntY = 1;
			}
			else  // RED
			{
				cntX = 1;
				cntY = 0;
			}
			
			/*
			// 색상 순서대로 변경
			++cntX;

			if (cntX == 4)
			{
				cntX = 0;
				++cntY;

				if (cntY == 2)
					cntY = 0;
			}
			*/

			Sleep(80);
		}
	}
}

void Tile::Render(HDC _hdc)
{
	BitBlt(_hdc,
		int(position.x - (scale.x * 0.5f)),
		int(position.y - (scale.y * 0.5f)),
		(int)scale.x,
		(int)scale.y,
		(*m_pImageList)[Key]->GetMemDC(),
		int(scale.x * cntX),
		int(scale.y * cntY),
		SRCCOPY);

	/*
	TransparentBlt(_hdc,
		int(position.x - (scale.x * 0.5f)),
		int(position.y - (scale.y * 0.5f)),
		(int)scale.x,
		(int)scale.y,
		(*m_pImageList)[Key]->GetMemDC(),
		int(scale.x * cntX),
		int(scale.y * cntY),
		(int)scale.x,
		(int)scale.y,
		RGB(255, 255, 255));
	*/

	/*
	if(check)
		Rectangle(_hdc, 
			int(position.x - (scale.x * 0.5f)),
			int(position.y - (scale.y * 0.5f)),
			int(position.x + (scale.x * 0.5f)),
			int(position.y + (scale.y * 0.5f)));
	else
		Ellipse(_hdc, 
			int(position.x - (scale.x * 0.5f)),
			int(position.y - (scale.y * 0.5f)),
			int(position.x + (scale.x * 0.5f)),
			int(position.y + (scale.y * 0.5f)));
	*/
}

void Tile::Destroy()
{

}
