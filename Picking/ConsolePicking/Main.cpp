#define _CRT_SECURE_NO_WARNINGS  // _itoa 함수 에러 안 뜨게 하려고 사용(맨 위에 써야 함)
#include <iostream>
#include <Windows.h>

using namespace std;

// ** 타일 가로, 세로 최대 개수
#define COUNT_X 7
#define COUNT_Y 4

// ** 텍스트 색
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


typedef struct tagVector3  // tag: 동일한 이름으로 생성되는 걸 방지하는 목적. typedef 키워드가 있음을 의미
{
	float x, y;

	tagVector3() : x(0.0f), y(0.0f) {}
	tagVector3(float _x, float _y) : x(_x), y(_y) {}
} Vector3;


void SetCursorPosition(const float& _x, const float& _y);
void SetColor(int _color);
void Text(const float& _x, const float& _y, const string& _str);


int main(void)
{
	// ** 타일 위치
	Vector3 position;
	position.x = 55;  // 시작점 x
	position.y = 13;  // 시작점 y

	// ** 타일 크기
	Vector3 scale;
	scale.x = 6;  // 문자열의 길이
	scale.y = 3;

	ULONGLONG time = GetTickCount64();

	// 계속 덮어써서 깜박거리는 현상 발생(잔상 남는 것) -> system(""cls"); 필요
	// -> 그래도 깜박이는데 time + 50 해주면 됨
	// -> 여전히 있으면 어쩔 수 없음. 버퍼가 하나뿐이라 쓰고 지우는 게 보이는 것
	while (true)
	{
		if (time + 50 < GetTickCount64())
		{
			time = GetTickCount64();

			// ** 화면 청소
			system("cls");

			for (int y = 0; y < COUNT_Y; ++y)
			{
				for (int x = 0; x < COUNT_X; ++x)
				{
					/*Text(position.x + scale.x * x,
						position.y + scale.y * y,
						"┌─┐");

					Text(position.x + scale.x * x,
						position.y + scale.y * y + 1,
						"│　│");

					Text(position.x + scale.x * x,
						position.y + scale.y * y + 2,
						"└─┘");*/

					SetColor(7);

					// ** 타일 출력
					Text(position.x - (scale.x * 0.5f) + scale.x * x,
						position.y - (scale.y * 0.5f) + scale.y * y,
						"┌─┐");

					Text(position.x - (scale.x * 0.5f) + scale.x * x,
						position.y - (scale.y * 0.5f) + scale.y * y + 1,
						"│　│");

					Text(position.x - (scale.x * 0.5f) + scale.x * x,
						position.y - (scale.y * 0.5f) + scale.y * y + 2,
						"└─┘");

					// ** index 확인
					int index = y * COUNT_X + x;  // y: 몇 번째 칸에 있는지, cntX: 몇 개까지 출력하는지, x: 1씩 증가하며 더해줌

					char* buffer = new char[4];
					_itoa(index, buffer, 10); // int to ascii

					SetColor(12);  // 한번 바꾸면 계속 바껴 있으므로 맨 위에 SetColor(7);(기본색) 필요. 아래에도 필요(콘솔창 맨 아래 설명? 텍스트색은 변경 안 되도록).

					Text(position.x - 1 + scale.x * x,  // 밀리기 때문에 한 칸 앞으로
						position.y - (scale.y * 0.5f) + scale.y * y + 1,
						string(buffer));


					// ** CPU가 연산을 하지 않는 상태
					Sleep(50);
				}
			}
		}
	}

	
	
	SetColor(7);

	return 0;
}

void SetCursorPosition(const float& _x, const float& _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(int _color)
{
	/*
	// #1.
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _color);  // GetStdHandle(): api GetDC 함수와 비슷. STD_OUTPUT_HANDLE은 콘솔창 속성 받아오겠다는 것(기본 핸들). 출력하는 핸들?

	// #2.
	HANDLE handle;  // 핸들 직접 만들 수도 있음. 위의 출력하는? 핸들과 다름. 더블 버퍼 사용할 때 주로 핸들 만들어서 사용.

	SetConsoleTextAttribute(
		handle, _color);
	*/

	// #3.
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(
		handle, _color);
}

void Text(const float& _x, const float& _y, const string& _str)
{
	SetCursorPosition(_x, _y);
	cout << _str << endl;
}
