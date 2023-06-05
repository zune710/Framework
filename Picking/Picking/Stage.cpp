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

	// ���� ����
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

	// �ɼ� ���� 0.1�ʵ��� Swap
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

	// ** ��� Ÿ���� Ȯ��
	// ** �ֺ� Ÿ�� �߿� ���ڰ� �� �� �ִ��� Ȯ�� �� Ÿ���� ����
	for (int i = 0; i < TileList.size(); ++i)
	{
		if (TileList[i]->GetOption() == 10)
			continue;

		int count = 0;

		// ��
		int index = TileList[i]->GetIndex() - COUNT_X;
		if (0 <= index && TileList[index]->GetOption() == 10)
			++count;

		// ������ ��
		index = TileList[i]->GetIndex() - COUNT_X + 1;
		if (0 <= index && index < MAX && index % COUNT_X != 0 &&
			TileList[index]->GetOption() == 10)
			++count;

		// ������
		index = TileList[i]->GetIndex() + 1;
		if (index < MAX && index % COUNT_X != 0 && TileList[index]->GetOption() == 10)
			++count;

		// ������ �Ʒ�
		index = TileList[i]->GetIndex() + COUNT_X + 1;
		if (index < MAX && index % COUNT_X != 0 && index < MAX &&
			TileList[index]->GetOption() == 10)
			++count;

		// �Ʒ�
		index = TileList[i]->GetIndex() + COUNT_X;
		if (index < MAX && TileList[index]->GetOption() == 10)
			++count;

		// ���� �Ʒ�
		index = TileList[i]->GetIndex() + COUNT_X - 1;
		if (0 <= index && index < MAX && index % COUNT_X != COUNT_X - 1 &&
			TileList[index]->GetOption() == 10)
			++count;

		// ����
		index = TileList[i]->GetIndex() - 1;
		if(0 <= index && index % COUNT_X != COUNT_X - 1 && 
			TileList[index]->GetOption() == 10)
			++count;

		// ���� ��
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
			// ** ����
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
