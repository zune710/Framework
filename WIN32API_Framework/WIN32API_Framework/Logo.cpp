#include "Logo.h"
#include "SceneManager.h"
#include "InputManager.h"

Logo::Logo()
{
}

Logo::~Logo()
{
}

void Logo::Start()
{

}

int Logo::Update()
{
	DWORD dwKey = GetSingle(InputManager)->GetKey();

	if (dwKey & KEYID_RETURN)
	{
		Sleep(100);
		GetSingle(SceneManager)->SetScene(MENU);
	}
	
	return 0;
}

void Logo::Render(HDC hdc)
{
	Rectangle(hdc, 500, 500, 600, 600);
}

void Logo::Destroy()
{

}
