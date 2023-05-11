#include "Menu.h"
#include "SceneManager.h"
#include "InputManager.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Start()
{

}

int Menu::Update()
{
	DWORD dwKey = GetSingle(InputManager).GetKey();
	//DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEYID_RETURN)
	{
		Sleep(100);
		GetSingle(SceneManager).SetScene(STAGE);
		//SceneManager::GetInstance()->SetScene(STAGE);
	}
	
	return 0;
}

void Menu::Render(HDC hdc)
{
	Ellipse(hdc, 500, 500, 600, 600);

}

void Menu::Destroy()
{

}
