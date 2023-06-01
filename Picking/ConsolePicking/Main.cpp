#define _CRT_SECURE_NO_WARNINGS  // _itoa �Լ� ���� �� �߰� �Ϸ��� ���(�� ���� ��� ��)
#include <iostream>
#include <Windows.h>
#include <vector>
#include <list>

using namespace std;

// ** Ÿ�� ����, ���� �ִ� ����
#define COUNT_X 5
#define COUNT_Y 5


// ** �ؽ�Ʈ ��
#define BLACK		0
#define DARKBLUE	1
#define DARKGREEN	2
#define DARKSKYBLUE 3
#define DARKRED		4
#define DARKPURPLE	5
#define DARKYELLOW	6
#define GRAY		7
#define DARKGRAY	8
#define BLUE		9
#define GREEN		10
#define SKYBLUE		11
#define RED			12
#define PURPLE		13
#define YELLOW		14
#define WHITE		15


void SetCursorPosition(const float& _x, const float& _y);
void SetColor(const int& _color);
void Text(const float& _x, const float& _y, const string& _str, int _color);
bool CheckTileList(int _index);

typedef struct tagVector3
{
	float x, y;

	tagVector3() : x(0.0f), y(0.0f) {}
	tagVector3(float _x, float _y) : x(_x), y(_y) {}
} Vector3;

typedef struct tagTile
{
	Vector3 position[3];
	string tile[3];
	int option;
	int index;
	int color;

	void Render(int _color = 15)
	{
		for (int i = 0; i < 3; ++i)
			Text(position[i].x, position[i].y, tile[i], _color);

		char* buffer = new char[4];

		_itoa(index, buffer, 10);

		Text(position[1].x + 2, position[1].y, string(buffer), _color);
	}

	tagTile() : option(0), index(0) {}
} Tile;

typedef struct tagInfo
{
	Vector3 position;
	int option;

	tagInfo() : option(0) {}
} Info;


// ** Ÿ�� ũ��
const Vector3 scale(6, 3);

const int MAX = COUNT_X * COUNT_Y;

list<Tile*> BlackTileList;


int main(void)
{
	BlackTileList.clear();

	// ** Ÿ�� ��ġ
	vector<Tile*> TileList;

	int x = 0;
	int y = 0;

	for (int i = 0; i < COUNT_Y * COUNT_X; ++i)
	{
		Tile* tile = new Tile;

		tile->tile[0] = "������";
		tile->position[0] = Vector3(x * scale.x, y * scale.y);

		tile->tile[1] = "������";
		tile->position[1] = Vector3(x * scale.x, y * scale.y + 1);

		tile->tile[2] = "������";
		tile->position[2] = Vector3(x * scale.x, y * scale.y + 2);

		tile->option = 0;
		tile->color = 15;
		tile->index = y * COUNT_X + x;

		x++;

		if (x == 5)
		{
			x = 0;
			y++;
		}

		TileList.push_back(tile);
	}

	// ** Target
	Info Cursor;

	Cursor.position = Vector3(15.0f, 8.0f);
	Cursor.option = 0;

	srand((unsigned int)GetTickCount64());
	
	for (int i = 0; i < 3; ++i)
	{
		int random = rand() % 25;

		TileList[random]->option = 1;

		BlackTileList.push_back(TileList[random]);
	}


	// ** Ŀ���� ��ġ�� Ÿ���� �ε���
	int X = int(Cursor.position.x / scale.x);
	int Y = int(Cursor.position.y / scale.y);

	int index = Y * COUNT_X + X;


	ULONGLONG time = GetTickCount64();

	while (true)
	{
		if (time + 100 < GetTickCount64())
		{
			time = GetTickCount64();

			// ** ȭ�� û��
			system("cls");

			/*
			if(!(MAX <= index))
				TileList[index]->color = 12;
			*/

			/*
			for (vector<Tile*>::iterator iter = TileList.begin(); iter != TileList.end(); ++iter)
				(*iter)->Render();
			*/

			if (GetAsyncKeyState(VK_SPACE))
				index = 0;

			if (GetAsyncKeyState(VK_UP))
			{
				if (0 < index && index < MAX && CheckTileList(index - COUNT_X))
					index -= COUNT_X;
			}
			//TileList[index - COUNT_X]->option == 0 ��� CheckTileList �Լ� ���

			if (GetAsyncKeyState(VK_DOWN))
			{
				if (0 <= index && index < MAX && CheckTileList(index + COUNT_X))
					index += COUNT_X;
			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				if (0 < index && index < MAX && CheckTileList(index - 1))
					index -= 1;
			}

			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (0 <= index && index < MAX && CheckTileList(index + 1))
					index += 1;
			}


			for (int i = 0; i < TileList.size(); ++i)
			{
				if (index == i)
					TileList[i]->Render(12);
				else
				{
					if (TileList[i]->option == 1)
						TileList[i]->Render(0);
					else
						TileList[i]->Render(15);
				}
			}

			// ** CPU�� ������ ���� �ʴ� ����
			Sleep(50);
		}
	}

	SetColor(7);

	return 0;
}

void SetCursorPosition(const float& _x, const float& _y)
{
	COORD pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(const int& _color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, _color);
}

void Text(const float& _x, const float& _y, const string& _str, int _color = 15)
{
	SetColor(_color);
	SetCursorPosition(_x, _y);
	cout << _str << endl;
}

bool CheckTileList(int _index)
{
	for (list<Tile*>::iterator iter = BlackTileList.begin(); iter != BlackTileList.end(); ++iter)
	{
		if ((*iter)->index == _index || _index < 0 || _index >= MAX)
			return false;
	}
	return true;
}