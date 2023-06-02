#define _CRT_SECURE_NO_WARNINGS  // _itoa 함수 에러 안 뜨게 하려고 사용(맨 위에 써야 함)
#include <iostream>
#include <Windows.h>
#include <vector>
#include <list>

using namespace std;

// ** 타일 가로, 세로 최대 개수
#define COUNT_X 5
#define COUNT_Y 5

// ** 타일 최대 개수
const int MAX = COUNT_X * COUNT_Y;

// ** 색
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

// ** 전방 선언
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
	Vector3 position[4];
	string tile[4];
	int option;
	int index;
	int value;
	int color;
	bool check;

	void Render()
	{
		switch (option)
		{
		case 0:
			color = WHITE;
			break;

		case 1:
			color = RED;
			break;
		}

		for (int i = 0; i < 4; ++i)
			Text(position[i].x, position[i].y, tile[i], color);

		/*
		char* buffer = new char[4];

		_itoa(value, buffer, 10);  // 값 랜덤 출력

		Text(position[1].x + 2, position[1].y, string(buffer), color);
		*/
	}

	tagTile() : option(0), index(0), value(0), color(15), check(false) {}
} Tile;

typedef struct tagInfo
{
	Vector3 position;
	int option;

	tagInfo() : option(0) {}
} Info;


// ** 타일 크기
const Vector3 scale(6, 3);

list<Tile*> BlackTileList;


int main(void)
{
	BlackTileList.clear();

	// ** 타일 위치
	vector<Tile*> TileList;

	int x = 0;
	int y = 0;

	for (int i = 0; i < COUNT_Y * COUNT_X; ++i)
	{
		Tile* tile = new Tile;

		tile->tile[0] = "┌─┐";
		tile->position[0] = Vector3(x * scale.x, y * scale.y);

		tile->tile[1] = "│　│";
		tile->position[1] = Vector3(x * scale.x, y * scale.y + 1);

		tile->tile[2] = "└─┘";
		tile->position[2] = Vector3(x * scale.x, y * scale.y + 2);

		tile->option = 0;
		tile->color = WHITE;
		tile->index = y * COUNT_X + x;
		tile->value = tile->index + 1;
		tile->check = true;

		x++;

		if (x == 5)
		{
			x = 0;
			y++;
		}

		TileList.push_back(tile);
	}

	// 값 랜덤 출력
	srand((unsigned int)GetTickCount64());

	for (int i = 0; i < COUNT_Y * COUNT_X * 2; ++i)
	{
		int random1 = rand() % 25;
		int random2 = rand() % 25;

		if (random1 == random2)
			continue;
		else
		{
			int value = TileList[random1]->value;
			TileList[random1]->value = TileList[random2]->value;
			TileList[random2]->value = value;
		}
	}


	for (int i = 0; i < COUNT_Y * COUNT_X; ++i)
	{
		char* buffer = new char[4];

		_itoa(TileList[i]->value, buffer, 10);

		TileList[i]->position[3] = Vector3(TileList[i]->position[1].x + 2, TileList[i]->position[1].y);
		TileList[i]->tile[3] = string(buffer);
	}


	/*  // 랜덤으로 3개의 타일을 빈 타일로 만듦
	srand((unsigned int)GetTickCount64());

	for (int i = 0; i < 3; ++i)
	{
		int random = rand() % 25;

		TileList[random]->option = 1;

		BlackTileList.push_back(TileList[random]);
	}
	*/



	// ** Target
	Info Cursor;

	Cursor.position = Vector3(15.0f, 8.0f);
	Cursor.option = 0;

	// ** 커서가 위치한 타일의 인덱스
	int X = int(Cursor.position.x / scale.x);
	int Y = int(Cursor.position.y / scale.y);

	int index = Y * COUNT_X + X;


	ULONGLONG time = GetTickCount64();

	while (true)
	{
		if (time + 100 < GetTickCount64())
		{
			time = GetTickCount64();

			// ** 화면 청소
			system("cls");

			if (GetAsyncKeyState(VK_RETURN))
				index = 0;

			if (GetAsyncKeyState(VK_UP))
			{
				if (COUNT_X < index && CheckTileList(index - COUNT_X))
					index -= COUNT_X;
			}

			if (GetAsyncKeyState(VK_DOWN))
			{
				if (index < (MAX - COUNT_X) && CheckTileList(index + COUNT_X))
					index += COUNT_X;
			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				if (index % 5 != 0 && CheckTileList(index - 1))
					index -= 1;
			}

			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (index % 5 != 4 && CheckTileList(index + 1))
					index += 1;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				Text(57, 14, "Input!", 10);
				TileList[index]->option = !TileList[index]->option;
			}

			// ** 출력
			for (int i = 0; i < TileList.size(); ++i)
			{
				if (index == i)
				{
					int Color;

					if (TileList[index]->option)
						Color = YELLOW;
					else
						Color = GREEN;

					for(int j = 0; j < 4; ++j)
						Text(TileList[index]->position[j].x,
							TileList[index]->position[j].y,
							TileList[index]->tile[j],
							Color);
					/*
					Text(TileList[index]->position[0].x, 
						TileList[index]->position[0].y, 
						TileList[index]->tile[0],
						GREEN);

					Text(TileList[index]->position[1].x,
						TileList[index]->position[1].y,
						TileList[index]->tile[1],
						GREEN);

					Text(TileList[index]->position[2].x,
						TileList[index]->position[2].y,
						TileList[index]->tile[2],
						GREEN);

					Text(TileList[index]->position[3].x,
						TileList[index]->position[3].y,
						TileList[index]->tile[3],
						GREEN);
					*/
				}
				else
					TileList[i]->Render();
				

				/*
				if (index == i)
					TileList[i]->Render(12);
				else
				{
					if (TileList[i]->option == 1)
						TileList[i]->Render(0);
					else
						TileList[i]->Render(15);
				}
				*/
			}

			// ** CPU가 연산을 하지 않는 상태
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
		if ((*iter)->index == _index)
			return false;
	}
	return true;
}