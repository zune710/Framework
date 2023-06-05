#include "Stage.h"
#include "Tile.h"
#include "Bitmap.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	Destroy();
}

void Stage::Start()
{
	ImageList["Tile"] = (new Bitmap)->LoadBmp(L"../Resource/Tile.bmp");

	// 지뢰 개수
	int mine = 150;

	for (int y = 0; y < COUNT_Y; ++y)
	{
		for (int x = 0; x < COUNT_X; ++x)
		{
			Object* tile = new Tile;
			tile->Start();
			
			if (mine)
			{
				--mine;
				tile->SetOption(10);
			}

			tile->SetIndex(y * COUNT_X + x);

			tile->SetPosition(Vector3(
				(x * SCALE_X) + (SCALE_X * 0.5f), 
				(y * SCALE_Y) + (SCALE_Y * 0.5f)));

			TileList.push_back(tile);
		}
	}

	ULONGLONG Time = GetTickCount64();

	// 옵션 랜덤 0.1초동안 Swap
	while (true)
	{
		if (Time + 100 > GetTickCount64())
		{
			int temp, dest;

			temp = rand() % TileList.size();
			dest = rand() % TileList.size();

			if (temp == dest)
				continue;

			int pTile = TileList[temp]->GetOption();
			TileList[temp]->SetOption(TileList[dest]->GetOption());
			TileList[dest]->SetOption(pTile);
		}
		else
			break;
	}

	// ** 모든 타일을 확인
	// ** 주변 타일 중에 지뢰가 몇 개 있는지 확인 후 타일을 설정
	for (int i = 0; i < TileList.size(); ++i)
	{
		if (TileList[i]->GetOption() == 10)
			continue;

		int count = 0;

		// 위
		int index = TileList[i]->GetIndex() - COUNT_X;
		if (0 <= index && TileList[index]->GetOption() == 10)
			++count;

		// 오른쪽 위
		index = TileList[i]->GetIndex() - COUNT_X + 1;
		if (0 <= index && index < MAX && index % COUNT_X != 0 &&
			TileList[index]->GetOption() == 10)
			++count;

		// 오른쪽
		index = TileList[i]->GetIndex() + 1;
		if (index < MAX && index % COUNT_X != 0 && TileList[index]->GetOption() == 10)
			++count;

		// 오른쪽 아래
		index = TileList[i]->GetIndex() + COUNT_X + 1;
		if (index < MAX && index % COUNT_X != 0 && index < MAX &&
			TileList[index]->GetOption() == 10)
			++count;

		// 아래
		index = TileList[i]->GetIndex() + COUNT_X;
		if (index < MAX && TileList[index]->GetOption() == 10)
			++count;

		// 왼쪽 아래
		index = TileList[i]->GetIndex() + COUNT_X - 1;
		if (0 <= index && index < MAX && index % COUNT_X != COUNT_X - 1 &&
			TileList[index]->GetOption() == 10)
			++count;

		// 왼쪽
		index = TileList[i]->GetIndex() - 1;
		if(0 <= index && index % COUNT_X != COUNT_X - 1 && 
			TileList[index]->GetOption() == 10)
			++count;

		// 왼쪽 위
		index = TileList[i]->GetIndex() - COUNT_X - 1;
		if (0 <= index && index % COUNT_X != COUNT_X - 1 &&
			TileList[index]->GetOption() == 10)
			++count;

		TileList[i]->SetOption(count + 1);
	}





	Object::SetImageList(&ImageList);
}

void Stage::Update()
{
	for (vector<Object*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
	{
		int result = (*iter)->Update();

		if (result == 1)
		{
			// ** 지뢰
		}
	}
}

void Stage::Render(HDC _hdc)
{
	for (vector<Object*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
	{
		(*iter)->Render(_hdc);
	}
}

void Stage::Destroy()
{
	for (vector<Object*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	TileList.clear();
}
