#include "Tile.h"
#include "Bitmap.h"

Tile::Tile() : hor(0), ver(0)
{
}

Tile::~Tile()
{
}

void Tile::Start()
{
	position = Vector3(100.0f, 100.0f);
	scale = Vector3(SCALE_X, SCALE_Y);

	Option = 7;

	hor = 0;
	ver = 0;
}

int Tile::Update()
{
	POINT ptMouse;

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	if (position.x - (scale.x * 0.5f) < ptMouse.x &&
		position.y - (scale.y * 0.5f) < ptMouse.y &&
		ptMouse.x < position.x + (scale.x * 0.5f) &&
		ptMouse.y < position.y + (scale.y * 0.5f))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			hor = Option;

			if (hor >= 10)
				return 1;  // ** Áö·Ú

			Sleep(80);
		}

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)  // ±ê¹ß
		{
			if (!hor)
				hor = 11;
			else if (hor == 11)
				hor = 0;

			Sleep(100);
		}
	}

	if (GetAsyncKeyState(VK_TAB))
	{
		hor = Option;
	}

	return 0;
}

void Tile::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		int(position.x - (scale.x * 0.5f)),
		int(position.y - (scale.y * 0.5f)),
		(int)scale.x,
		(int)scale.y,
		(*ImageList)["Tile"]->GetMemDC(),
		int(scale.x * hor),
		int(scale.y * ver),
		(int)scale.x,
		(int)scale.y,
		RGB(255, 0, 255));
	
	/*
	BitBlt(_hdc,
		int(position.x - (scale.x * 0.5f)),
		int(position.y - (scale.y * 0.5f)),
		(int)scale.x,
		(int)scale.y,
		(*ImageList)["Tile"]->GetMemDC(),
		int(scale.x * hor),
		int(scale.y * ver),
		SRCCOPY);
	*/
}

void Tile::Destroy()
{

}
