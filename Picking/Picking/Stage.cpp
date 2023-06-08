#include "Stage.h"
#include "Tile.h"
#include "Bitmap.h"
#include "Button.h"

Stage::Stage() : Result(0)
{
}

Stage::~Stage()
{
	Destroy();
}

void Stage::Start()
{
	ImageList["Tile"] = (new Bitmap)->LoadBmp(L"../Resource/Tile.bmp");
	ImageList["Buffer"] = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList["GameOver"] = (new Bitmap)->LoadBmp(L"../Resource/GameOver.bmp");
	ImageList["GameClear"] = (new Bitmap)->LoadBmp(L"../Resource/GameClear.bmp");

	ImageList["MenuBar"] = (new Bitmap)->LoadBmp(L"../Resource/MenuBar.bmp");
	ImageList["Icon_GamePlay"] = (new Bitmap)->LoadBmp(L"../Resource/Icon_GamePlay.bmp");
	ImageList["Icon_GameOver"] = (new Bitmap)->LoadBmp(L"../Resource/Icon_GameOver.bmp");
	ImageList["Icon_GameClear"] = (new Bitmap)->LoadBmp(L"../Resource/Icon_GameClear.bmp");
	ImageList["Restart"] = (new Bitmap)->LoadBmp(L"../Resource/Restart.bmp");

	// 지뢰 개수
	int mine = 150;

	for (int y = 0; y < COUNT_Y; ++y)
	{
		for (int x = 0; x < COUNT_X; ++x)
		{
			Object* tile = new Tile;
			tile->Start();
			
			tile->SetIndex(y * COUNT_X + x);

			if (mine)
			{
				--mine;
				tile->SetOption(10);
			}

			tile->SetPosition(Vector3(
				(x * SCALE_X) + (SCALE_X * 0.5f), 
				(y * SCALE_Y) + (SCALE_Y * 0.5f) + 64));

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
		if (0 <= index &&
			TileList[i]->GetPosition().x < TileList[index]->GetPosition().x &&
			TileList[index]->GetOption() == 10)
			++count;

		// 오른쪽
		index = TileList[i]->GetIndex() + 1;
		if (index < MAX && 
			TileList[i]->GetPosition().x < TileList[index]->GetPosition().x && 
			TileList[index]->GetOption() == 10)
			++count;

		// 오른쪽 아래
		index = TileList[i]->GetIndex() + COUNT_X + 1;
		if (index < MAX && 
			TileList[i]->GetPosition().x < TileList[index]->GetPosition().x &&
			TileList[index]->GetOption() == 10)
			++count;

		// 아래
		index = TileList[i]->GetIndex() + COUNT_X;
		if (index < MAX && TileList[index]->GetOption() == 10)
			++count;

		// 왼쪽 아래
		index = TileList[i]->GetIndex() + COUNT_X - 1;
		if (index < MAX && 
			TileList[index]->GetPosition().x < TileList[i]->GetPosition().x &&
			TileList[index]->GetOption() == 10)
			++count;

		// 왼쪽
		index = TileList[i]->GetIndex() - 1;
		if(0 <= index && 
			TileList[index]->GetPosition().x < TileList[i]->GetPosition().x &&
			TileList[index]->GetOption() == 10)
			++count;

		// 왼쪽 위
		index = TileList[i]->GetIndex() - COUNT_X - 1;
		if (0 <= index && 
			TileList[index]->GetPosition().x < TileList[i]->GetPosition().x &&
			TileList[index]->GetOption() == 10)
			++count;

		TileList[i]->SetOption(count + 1);
	}

	Object::SetImageList(&ImageList);

	Restart = new Button;
	Restart->Start();
	
}

void Stage::Update()
{
	for (vector<Object*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
	{	
		if ((*iter)->Update() == 1)
		{
			// ** 지뢰
			Result = 1;
		}
	}

	// ** 빈 타일 클릭하면 주변 타일 열기
	for (int i = 0; i < TileList.size(); ++i)
	{
		if (((Tile*)TileList[i])->GetHorizontal() == 1)
		{
			// 위
			int index = TileList[i]->GetIndex() - COUNT_X;
			if (0 <= index)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 오른쪽 위
			index = TileList[i]->GetIndex() - COUNT_X + 1;
			if (0 <= index && index < MAX && TileList[i]->GetPosition().x < TileList[index]->GetPosition().x)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 오른쪽
			index = TileList[i]->GetIndex() + 1;
			if (index < MAX && TileList[i]->GetPosition().x < TileList[index]->GetPosition().x)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 오른쪽 아래
			index = TileList[i]->GetIndex() + COUNT_X + 1;
			if (index < MAX &&
				TileList[i]->GetPosition().x < TileList[index]->GetPosition().x)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 아래
			index = TileList[i]->GetIndex() + COUNT_X;
			if (index < MAX)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 왼쪽 아래
			index = TileList[i]->GetIndex() + COUNT_X - 1;
			if (0 <= index && index < MAX && TileList[index]->GetPosition().x < TileList[i]->GetPosition().x)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 왼쪽
			index = TileList[i]->GetIndex() - 1;
			if (0 <= index && TileList[index]->GetPosition().x < TileList[i]->GetPosition().x)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());

			// 왼쪽 위
			index = TileList[i]->GetIndex() - COUNT_X - 1;
			if (0 <= index && TileList[index]->GetPosition().x < TileList[i]->GetPosition().x)
				((Tile*)TileList[index])->SetHorizontal(TileList[index]->GetOption());
		}
	}

	int count = 0;
	for (int i = 0; i < TileList.size(); ++i)
	{
		if (count > 150)
			break;

		if (((Tile*)TileList[i])->GetHorizontal() == 0 || ((Tile*)TileList[i])->GetHorizontal() == 11)
			++count;
	}

	if (count == 150)
	{
		for (int i = 0; i < TileList.size(); ++i)
		{
			if (((Tile*)TileList[i])->GetHorizontal() == 0)
				((Tile*)TileList[i])->SetHorizontal(11);
		}

		Result = 2; // 게임 클리어
	}

	if(Restart)
		Restart->Update();

}

void Stage::Render(HDC _hdc)
{
	for (vector<Object*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
		(*iter)->Render(ImageList["Buffer"]->GetMemDC());

	TransparentBlt(ImageList["Buffer"]->GetMemDC(),
		0, 0,
		WIDTH, 64,
		ImageList["MenuBar"]->GetMemDC(),
		0, 0,
		WIDTH, 64,
		RGB(255, 0, 255));

	if (Restart)
		Restart->Render(ImageList["Buffer"]->GetMemDC());

	if (Result == 1)  // 지뢰 - Game Over
	{
		for (vector<Object*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
		{
			((Tile*)*iter)->SetHorizontal((*iter)->GetOption());
			
		}
		
		TransparentBlt(ImageList["Buffer"]->GetMemDC(),
			int(WIDTH * 0.5f - 22), 10,
			44, 44,
			ImageList["Icon_GameOver"]->GetMemDC(),
			0, 0,
			44, 44,
			RGB(255, 0, 255));
		
		/*
		TransparentBlt(ImageList["Buffer"]->GetMemDC(),
			0, 0,
			int(COUNT_X * SCALE_X), int(COUNT_Y * SCALE_Y),
			ImageList["GameOver"]->GetMemDC(),
			0, 0,
			int(COUNT_X * SCALE_X), int(COUNT_Y * SCALE_Y),
			RGB(255, 0, 255));
		*/
	}
	else if (Result == 2)
	{
		TransparentBlt(ImageList["Buffer"]->GetMemDC(),
			int(WIDTH * 0.5f - 22), 10,
			44, 44,
			ImageList["Icon_GameClear"]->GetMemDC(),
			0, 0,
			44, 44,
			RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(ImageList["Buffer"]->GetMemDC(),
			int(WIDTH * 0.5f - 22), 10,
			44, 44,
			ImageList["Icon_GamePlay"]->GetMemDC(),
			0, 0,
			44, 44,
			RGB(255, 0, 255));
	}
		

	BitBlt(_hdc,
		0, 0,
		(int)WIDTH, (int)HEIGHT,
		ImageList["Buffer"]->GetMemDC(),
		0, 0, 
		SRCCOPY);
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
