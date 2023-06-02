#include "Stage.h"
#include "Tile.h"
#include "Bitmap.h"
#include "Object.h"
#include "ImageManager.h"

Stage::Stage() : ImageList(nullptr)
{
}

Stage::~Stage()
{
	Destroy();
}

void Stage::Start()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < COUNT_X * COUNT_Y; ++i)
	{
		Object* object = new Tile;
		object->Start();
		object->SetPosition(
			Vector3(object->GetScale().x * x + object->GetScale().x * 0.5f, 
				object->GetScale().y * y + object->GetScale().y * 0.5f));
		
		++x;

		if (x == COUNT_X)
		{
			x = 0;
			++y;
		}

		ObjectList.push_back(object);
	}
	

	ImageList = ImageManager::GetInstance()->GetList();

	(*ImageList)["Tile"] = (new Bitmap)->LoadBmp(L"../Resource/Tile.bmp");

	Object::SetImageList(ImageList);
}

void Stage::Update()
{
	for (list<Object*>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
		(*iter)->Update();

	//object->Update();
}

void Stage::Render(HDC _hdc)
{
	for (list<Object*>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
		(*iter)->Render(_hdc);
	
	//object->Render(_hdc);
}

void Stage::Destroy()
{
	for (list<Object*>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	
	//delete object;
	//object = nullptr;
}
