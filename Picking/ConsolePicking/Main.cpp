#define _CRT_SECURE_NO_WARNINGS  // _itoa �Լ� ���� �� �߰� �Ϸ��� ���(�� ���� ��� ��)
#include <iostream>
#include <Windows.h>

using namespace std;

// ** Ÿ�� ����, ���� �ִ� ����
#define COUNT_X 7
#define COUNT_Y 4

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


typedef struct tagVector3  // tag: ������ �̸����� �����Ǵ� �� �����ϴ� ����. typedef Ű���尡 ������ �ǹ�
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
	// ** Ÿ�� ��ġ
	Vector3 position;
	position.x = 55;  // ������ x
	position.y = 13;  // ������ y

	// ** Ÿ�� ũ��
	Vector3 scale;
	scale.x = 6;  // ���ڿ��� ����
	scale.y = 3;

	ULONGLONG time = GetTickCount64();

	// ��� ����Ἥ ���ڰŸ��� ���� �߻�(�ܻ� ���� ��) -> system(""cls"); �ʿ�
	// -> �׷��� �����̴µ� time + 50 ���ָ� ��
	// -> ������ ������ ��¿ �� ����. ���۰� �ϳ����̶� ���� ����� �� ���̴� ��
	while (true)
	{
		if (time + 50 < GetTickCount64())
		{
			time = GetTickCount64();

			// ** ȭ�� û��
			system("cls");

			for (int y = 0; y < COUNT_Y; ++y)
			{
				for (int x = 0; x < COUNT_X; ++x)
				{
					/*Text(position.x + scale.x * x,
						position.y + scale.y * y,
						"������");

					Text(position.x + scale.x * x,
						position.y + scale.y * y + 1,
						"������");

					Text(position.x + scale.x * x,
						position.y + scale.y * y + 2,
						"������");*/

					SetColor(7);

					// ** Ÿ�� ���
					Text(position.x - (scale.x * 0.5f) + scale.x * x,
						position.y - (scale.y * 0.5f) + scale.y * y,
						"������");

					Text(position.x - (scale.x * 0.5f) + scale.x * x,
						position.y - (scale.y * 0.5f) + scale.y * y + 1,
						"������");

					Text(position.x - (scale.x * 0.5f) + scale.x * x,
						position.y - (scale.y * 0.5f) + scale.y * y + 2,
						"������");

					// ** index Ȯ��
					int index = y * COUNT_X + x;  // y: �� ��° ĭ�� �ִ���, cntX: �� ������ ����ϴ���, x: 1�� �����ϸ� ������

					char* buffer = new char[4];
					_itoa(index, buffer, 10); // int to ascii

					SetColor(12);  // �ѹ� �ٲٸ� ��� �ٲ� �����Ƿ� �� ���� SetColor(7);(�⺻��) �ʿ�. �Ʒ����� �ʿ�(�ܼ�â �� �Ʒ� ����? �ؽ�Ʈ���� ���� �� �ǵ���).

					Text(position.x - 1 + scale.x * x,  // �и��� ������ �� ĭ ������
						position.y - (scale.y * 0.5f) + scale.y * y + 1,
						string(buffer));


					// ** CPU�� ������ ���� �ʴ� ����
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
		GetStdHandle(STD_OUTPUT_HANDLE), _color);  // GetStdHandle(): api GetDC �Լ��� ���. STD_OUTPUT_HANDLE�� �ܼ�â �Ӽ� �޾ƿ��ڴٴ� ��(�⺻ �ڵ�). ����ϴ� �ڵ�?

	// #2.
	HANDLE handle;  // �ڵ� ���� ���� ���� ����. ���� ����ϴ�? �ڵ�� �ٸ�. ���� ���� ����� �� �ַ� �ڵ� ���� ���.

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
