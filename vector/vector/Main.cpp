#include <iostream>

using namespace std;

int* Numbers = nullptr;
int Length = 0;

void push(int n)
{
	if (Numbers == nullptr)
	{
		Numbers = new int;
		*Numbers = n;
		++Length;
		return;
	}
	
	int* Temp = new int[Length + 1];

	for (int i = 0; i < Length; ++i)
		Temp[i] = Numbers[i];

	Temp[Length] = n;
	Numbers = Temp;
	++Length;
}

int main(void)
{
	push(10);
	push(20);
	push(30);
	push(40);
	
	for (int i = 0; i < Length; ++i)
	{
		cout << Numbers[i] << endl;
	}

	return 0;
}


#pragma region 0516
//#include <vector>
//#include <list>

//int main(void)
//{
	//01
/* 벡터와 리스트
vector<int> Numbers;

Numbers.push_back(10);
Numbers.pop_back();

Numbers.capacity();


list<int> NumberList;

NumberList.push_back(10);
NumberList.push_front(1);

NumberList.pop_back();
NumberList.pop_front();
*/

//02
//int i[10] = {int, int, int, int, int, int, int, int, int, int}; // 일렬로 붙어있음

//03
/*
// 데이터 추가 어려움
int n[5];

for (int i = 0; i < 5; ++i)
	n[i] = i;

//n[5] = 5;  // (X)

int n2[6];

for (int i = 0; i < 5; ++i)
	n2[i] = n[i];

n2[5] = 5;
*/

/*
// 데이터 삭제도 어려움(데이터의 연속성이 사라지기 때문)
int n[5];
bool b[5];

for (int i = 0; i < 5; ++i)
{
	n[i] = i;
	b[i] = true;
}

n[3] = 0;
b[3] = false;
// -> 데이터의 연속성이 사라짐

for (int i = 0; i < 5; ++i)
{
	if (b[i])  // 예외처리 필요
		cout << n[i] << endl;
}
*/

// => 그래서 데이터의 추가, 삭제가 필요한 경우에는 vector를 사용하지 않는다.


//04
/*
int* Numbers = new int[1];

Numbers[0] = 10;
Numbers[1] = 20;
// 길이가 1이므로 20이란 값은 존재하면 안 되지만
// 포인터이기 때문에 그 위치를 가리켜 출력을 하는 것은 가능 -> 위험

cout << Numbers[0] << endl;
cout << Numbers[1] << endl;  // 20 출력
cout << Numbers[2] << endl;
*/

//	return 0;
//}

//05
/*
int main(void)
{
	//스마트 포인터
	{
		int* a, * b;

		{
			int* n = new int;
			*n = 100;

			a = b = n;  // 3개(a, b, n)의 참조
		} // n 소멸, 2개(a, b)의 참조

		cout << *a << endl;  // 100
		cout << *b << endl << endl;  // 100

		(*a) = 200;

		cout << *a << endl;  // 200
		cout << *b << endl << endl;  // 200
	} // a, b 소멸, 0개의 참조 -> 스마트 포인터는 스스로 포인터를 지우게 된다.
	// 스마트 포인터(템플릿으로 만들어진 클래스)는 나를 참조하는 포인터 수를 보고 스스로 포인터를 지울지 말지 결정

	return 0;
}

//C# 가비지 콜렉터
class Vector3
{
public:
	Vector3() {}
	~Vector3() {}
};

typedef Vector3(*PVector3);

// #1.
//void Update()  // 반복 실행
//{
//	PVector3 vector = new Vector3;
//}  // 참조가 없기 때문에 가비지 콜렉터로 이동
//   // 매 프레임마다 가비지 컬렉터에 new Vector3가 쌓임

PVector3 vector; // 이 때문에...

// #2.
void Update()
{
	vector = new Vector3;

} // ...참조가 사라지지 않으므로 가비지 콜렉터로 이동 안 함
*/
#pragma endregion