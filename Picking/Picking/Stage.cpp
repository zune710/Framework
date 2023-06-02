#include "Stage.h"
#include "Tile.h"
#include "Bitmap.h"
#include "Object.h"
#include "ImageManager.h"

Stage::Stage() : object(nullptr), ImageList(nullptr)
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
		object->SetPosition(Vector3(32 * x, 32 * y));
		
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
	object->Update();
}

void Stage::Render(HDC _hdc)
{
	object->Render(_hdc);
}

void Stage::Destroy()
{
	delete object;
	object = nullptr;
}
