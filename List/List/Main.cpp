#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// 1. 함수 사용
// 2. 클래스 이해도

// for(초기문; 조건문; 증감문)
// ** 초기문: int i = 0;
// ** 조건문: i < 10;
// ** 증감문: ++i


#define function(x) (cout << x << endl)  // 매크로 함수

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
	//	obj->age = 34;  // static이어서 이렇게 사용
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
		
		if(bulletList[i].Update(i))  // point! 이런 식으로 예외처리 가능.
			cout << "player age 값이 " << i << "보다 작습니다." << endl;
	}

	//FAILED();
	// return 0: 정상종료
	// return 1, 2, 3, ...: 정상종료(특이케이스)
	// return -1: 오류발생

	int value = 10;

	if (player->Update(value))  // point!
		cout << "player age 값이 " << value << "보다 작습니다." << endl;
	*/

	return 0;
}







/* #01.
//float a;  // 0으로 초기화됨
//a = 10;  // 오류 발생(형식 지정자가 없음(데이터 타입이 없음)): 위의 float a와 다른 걸(서로 다른 방)로 인식하기 때문.
//float b = 0.0f;  // 0.0f를 올려놓고 x라는 방을 만들어 그곳에 0.0f를 넣어 준다.

// Framework.sln의 Define.h에 있는 것들: 런타임 이전에 올려 놓는 것들(전역변수, 정적변수, 상수, 리터럴 등)
// 전역변수이므로 런타임 이전에 데이터 올려 놓음  // cf. 글로벌변수: extern 사용한 변수
// 리터럴 상수 총 4개(1920, 1080, 0.5f(2개 사용), 0.0f)
float x = 1920 * 0.5f;
float y = 1080 * 0.5f;
float z = 0.0f;

// 리터럴 상수 총 3개. 위보다 효율적으로 보이지만 위의 형태를 많이 쓰는 이유는 반복해서 쓰는 상수가 있기 때문.
//float x = 960;
//float y = 540;
//float z = 0.0f;


int* function(int _value)
{

	const int i = 10;
	// const int i: symbolic 상수
	// 10: literal 상수. 데이터 한 번만 올려 놓음.

	//i = 20;  // (X)
	// lvalue: 변수, rvalue: 상수

	// return &_value;  // 문제됨. 주소값이 같아 같은 값을 가짐.
	int* temp = new int;  // 주소 바꿔줘야 같은 값으로 안 나감
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