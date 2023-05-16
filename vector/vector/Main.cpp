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
/* ���Ϳ� ����Ʈ
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
//int i[10] = {int, int, int, int, int, int, int, int, int, int}; // �Ϸķ� �پ�����

//03
/*
// ������ �߰� �����
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
// ������ ������ �����(�������� ���Ӽ��� ������� ����)
int n[5];
bool b[5];

for (int i = 0; i < 5; ++i)
{
	n[i] = i;
	b[i] = true;
}

n[3] = 0;
b[3] = false;
// -> �������� ���Ӽ��� �����

for (int i = 0; i < 5; ++i)
{
	if (b[i])  // ����ó�� �ʿ�
		cout << n[i] << endl;
}
*/

// => �׷��� �������� �߰�, ������ �ʿ��� ��쿡�� vector�� ������� �ʴ´�.


//04
/*
int* Numbers = new int[1];

Numbers[0] = 10;
Numbers[1] = 20;
// ���̰� 1�̹Ƿ� 20�̶� ���� �����ϸ� �� ������
// �������̱� ������ �� ��ġ�� ������ ����� �ϴ� ���� ���� -> ����

cout << Numbers[0] << endl;
cout << Numbers[1] << endl;  // 20 ���
cout << Numbers[2] << endl;
*/

//	return 0;
//}

//05
/*
int main(void)
{
	//����Ʈ ������
	{
		int* a, * b;

		{
			int* n = new int;
			*n = 100;

			a = b = n;  // 3��(a, b, n)�� ����
		} // n �Ҹ�, 2��(a, b)�� ����

		cout << *a << endl;  // 100
		cout << *b << endl << endl;  // 100

		(*a) = 200;

		cout << *a << endl;  // 200
		cout << *b << endl << endl;  // 200
	} // a, b �Ҹ�, 0���� ���� -> ����Ʈ �����ʹ� ������ �����͸� ����� �ȴ�.
	// ����Ʈ ������(���ø����� ������� Ŭ����)�� ���� �����ϴ� ������ ���� ���� ������ �����͸� ������ ���� ����

	return 0;
}

//C# ������ �ݷ���
class Vector3
{
public:
	Vector3() {}
	~Vector3() {}
};

typedef Vector3(*PVector3);

// #1.
//void Update()  // �ݺ� ����
//{
//	PVector3 vector = new Vector3;
//}  // ������ ���� ������ ������ �ݷ��ͷ� �̵�
//   // �� �����Ӹ��� ������ �÷��Ϳ� new Vector3�� ����

PVector3 vector; // �� ������...

// #2.
void Update()
{
	vector = new Vector3;

} // ...������ ������� �����Ƿ� ������ �ݷ��ͷ� �̵� �� ��
*/
#pragma endregion