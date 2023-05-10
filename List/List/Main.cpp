#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// 1. �Լ� ���
// 2. Ŭ���� ���ص�

// for(�ʱ⹮; ���ǹ�; ������)
// ** �ʱ⹮: int i = 0;
// ** ���ǹ�: i < 10;
// ** ������: ++i


#define function(x) (cout << x << endl)  // ��ũ�� �Լ�

#define Single(T)				    \
public:							    \
	static T& GetInstance()		    \
	{							    \
		static T instance;		    \
		return instance;		    \
	}							    \
private:						    \
	T(const T&) = delete;		    \
	T& operator=(const T&) = delete;

#define GetSingle(T) (T::GetInstance())

class Singleton
{
public:
	Single(Singleton);
	/*
private:
	static Singleton* Instance;
public:
	static Singleton* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new Singleton;

		return Instance;
	}
	*/
private:
	int Value;
public:
	int GetValue() { return Value; }
	void SetValue(int value) { Value = value; }
private:
	Singleton() : Value(0) {}
public:
	~Singleton() {}
};

//Singleton* Singleton::Instance = nullptr;


class Object
{
protected:
	string name;
	int age;
public:
	virtual void Start(int x) = 0;
	virtual int Update(int x) = 0;

	//static int Update(int x)
	//{
	//	Object* obj = new Object;
	//	obj->age = 34;  // static�̾ �̷��� ���
	//	//age = 34;  // (X)
	//}
};

class Player : public Object
{
public:
	virtual void Start(int x)override
	{
		age = x;
	}
	virtual int Update(int x)override
	{
		if (age < x)
			return 1;

		return 0;
	}
};

class Bullet : public Object
{
public:
	virtual void Start(int x)override
	{
		age = x;
	}
	virtual int Update(int x)override
	{
		if (age < x)
			return 1;

		return 0;
	}
};


int main(void)
{
	GetSingle(Singleton).SetValue(10);
	cout << GetSingle(Singleton).GetValue() << endl;
	
	/* #02.
	function(10);
	Object* player = new Player;

	int length = 16;
	Object* bulletList = new Bullet[length];

	for (int i = 0; i < length; ++i)
	{
		bulletList->Start(i);
		
		if(bulletList[i].Update(i))  // point! �̷� ������ ����ó�� ����.
			cout << "player age ���� " << i << "���� �۽��ϴ�." << endl;
	}

	//FAILED();
	// return 0: ��������
	// return 1, 2, 3, ...: ��������(Ư�����̽�)
	// return -1: �����߻�

	int value = 10;

	if (player->Update(value))  // point!
		cout << "player age ���� " << value << "���� �۽��ϴ�." << endl;
	*/

	return 0;
}







/* #01.
//float a;  // 0���� �ʱ�ȭ��
//a = 10;  // ���� �߻�(���� �����ڰ� ����(������ Ÿ���� ����)): ���� float a�� �ٸ� ��(���� �ٸ� ��)�� �ν��ϱ� ����.
//float b = 0.0f;  // 0.0f�� �÷����� x��� ���� ����� �װ��� 0.0f�� �־� �ش�.

// Framework.sln�� Define.h�� �ִ� �͵�: ��Ÿ�� ������ �÷� ���� �͵�(��������, ��������, ���, ���ͷ� ��)
// ���������̹Ƿ� ��Ÿ�� ������ ������ �÷� ����  // cf. �۷ι�����: extern ����� ����
// ���ͷ� ��� �� 4��(1920, 1080, 0.5f(2�� ���), 0.0f)
float x = 1920 * 0.5f;
float y = 1080 * 0.5f;
float z = 0.0f;

// ���ͷ� ��� �� 3��. ������ ȿ�������� �������� ���� ���¸� ���� ���� ������ �ݺ��ؼ� ���� ����� �ֱ� ����.
//float x = 960;
//float y = 540;
//float z = 0.0f;


int* function(int _value)
{

	const int i = 10;
	// const int i: symbolic ���
	// 10: literal ���. ������ �� ���� �÷� ����.

	//i = 20;  // (X)
	// lvalue: ����, rvalue: ���

	// return &_value;  // ������. �ּҰ��� ���� ���� ���� ����.
	int* temp = new int;  // �ּ� �ٲ���� ���� ������ �� ����
	return temp;
}

int main(void)
{
	int* value1 = function(10);
	int* value2 = function(20);

	cout << (*value1) << endl;
	cout << (*value2) << endl;

	return 0;
}
*/