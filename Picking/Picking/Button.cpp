#include "Button.h"
#include "Bitmap.h"
#include "SceneManager.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Start()
{
    position = Vector3(WIDTH - 114.0f, 32.0f);
    scale = Vector3(100.0f, 32.0f);
}

int Button::Update()
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
			GetSingle(SceneManager)->SetScene(STAGE);

			Sleep(80);
		}
	}

	return 0;
}

void Button::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		int(position.x - (scale.x * 0.5f)), int(position.y - (scale.y * 0.5f)),
		(int)scale.x, (int)scale.y,
		(*ImageList)["Restart"]->GetMemDC(),
		0, 0,
		(int)scale.x, (int)scale.y,
		RGB(255, 0, 255));
}

void Button::Destroy()
{
}
