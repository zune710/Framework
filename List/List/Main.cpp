#include <iostream>

using namespace std;

typedef struct tagNode
{
	tagNode* next;
	int value;
} NODE;

NODE* List;
NODE* End;
int Length;


void push(int value)
{
	/* End 사용하면 push할 때마다 찾을 필요 없음(큰 비용을 아낄 수 있음)
	NODE* nextNode = List;
	
	while (nextNode->next != nullptr)
		nextNode = nextNode->next;
	
	// create
	nextNode->next = new NODE;

	// initialize
	nextNode->next->next = nullptr;
	nextNode->next->value = value;

	++Length;
	*/

	// create
	NODE* node = new NODE;

	// initialize
	node->next = nullptr;
	node->value = value;

	End->next = node;
	End = node;
	
	++Length;
}

void insert(int count, int value)
{
	// ** 리스트에 담긴 총 원소의 개수보다 count의 값이 크다면
	// ** 값을 추가할 수 없으므로 종료
	if (Length < count)
		return;

	// ** 리스트를 들고옴
	NODE* nextNode = List;

	// ** 카운트의 값만큼 다음 노드로 이동
	while (0 < count)
	{
		--count;

		// ** 다음 노드로 이동
		nextNode = nextNode->next;
	}
	// ** 이동이 끝났다면 새로운 노드를 추가
	
	// ** 새로운 노드 생성
	NODE* newNode = new NODE;
	newNode->next = nullptr;
	newNode->value = value;

	// ** 다음 노드를 임시의 저장소에 저장
	NODE* tempNode = nextNode->next;

	// ** 다음 노드를 저장하는 저장소에 새로운 노드를 배치
	nextNode->next = newNode;

	// ** 새로운 노드가 가리키는 다음 노드를 임시공간에 있던 노드로 배치
	newNode->next = tempNode;

	++Length;
}

void remove(int count)
{
	// ** 리스트에 담긴 총 원소의 개수보다 count의 값이 크다면
	// ** 값을 추가할 수 없으므로 종료
	if (Length < count)
		return;

	// ** 리스트를 들고옴
	NODE* nextNode = List;

	// ** 카운트의 값만큼 다음 노드로 이동
	while (0 < count)
	{
		--count;

		// ** 다음 노드로 이동
		nextNode = nextNode->next;
	}
	// ** 이동이 끝났다면 노드를 삭제

	// ** 다다음 노드를 임시의 저장소에 저장
	NODE* tempNode = nextNode->next->next;
	
	// ** 다음 노드를 삭제
	delete nextNode->next;
	nextNode->next = nullptr;

	// ** 삭제된 공간에 임시 저장했던 노드를 세팅
	nextNode->next = tempNode;

	--Length;
}

void pop_back()
{
	NODE* nextNode = List;

	while (nextNode->next != End)
		nextNode = nextNode->next;
	
	delete nextNode->next;
	nextNode->next = nullptr;

	End = nextNode;
	
	--Length;
}

int main(void)
{
#pragma region 0511: swap
	/* 0511
	// a가 b를 가리키고 있을 때 c를 그 사이에 어떻게 추가할 것인가
	int a = 10;
	int b = 20;

	// swap 사용
	int temp = a;
	a = b;
	b = temp;

	cout << a << endl;
	cout << b << endl;
	*/
#pragma endregion
#pragma region 0512: pointer, int, stack
	/* 0512
	// ** 포인터
	int i = 10;  // 데이터(실제 값)를 받음
	int* n = &i;  // 데이터(주소)를 받음

	cout << i << endl;  // 10
	cout << *n << endl;  // 참조

	cout << &i << endl;  // 주소값 출력
	cout << n << endl;  // 주소값 출력

	*n = 20;
	cout << i << endl;  // 20


	// ** 포인터 예시에 int를 주로 쓰는 이유
	cout << sizeof(int*) << endl;  // sizeof(int*)는 x64(64bit)에서 8byte, x86(32bit)에서 4byte 
	// int의 표준(IEEE): short < int <= long
	// int는 가변적. PC 환경에 따라 사이즈가 달라짐
	// but int의 size가 x64에서 8byte가 아닌 4byte인 이유: 4byte(고정)인 long보다 클 수 없기 때문
	
	// 32비트(x86)에서 모든 포인터(주소)는 4바이트로 표현됨(넘을 수가 없음. 4바이트만으로 모든 주소 표현 가능)
	// -> int(4byte)에 들어감 : 포인터 예시에 int를 주로 쓰는 이유
	cout << sizeof(tagNode*) << endl;
	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(long*) << endl;

	NODE* node = new NODE;  // 힙 메모리에 저장된 20byte 데이터(ex. int 변수 5개인 구조체)의 주소값만 불러오면 4byte만으로 20byte 데이터 사용 가능.
	node->next = nullptr;  // (*node).next와 동일

	// 함수에 가져와서 사용하려면 참조하면 됨.
	// but 함수에 필요 이상의 매개변수 사용하면 과도한 스택 메모리 복사 발생(비용 많이 듦)
	
	// cf. 64비트(x64)에서 모든 포인터(주소)는 8바이트로 표현됨


	// ** 스택
	{
		{
			NODE* node = nullptr;
			{
				NODE* tempNode = new NODE;
				tempNode->next = nullptr;
				tempNode->value = 10;

				node = tempNode;

				cout << tempNode << endl;
			}   // ↓ 동일한 주소값 ↑
			cout << node << endl;
		}
	}
	*/
#pragma endregion

	// ** 첫 번째 노드
	// create
	List = new NODE;

	// initialize
	List->next = nullptr;
	List->value = 0;

	End = List;
	
	//=======================================

	push(10);
	push(20);
	push(30);
	push(40);

	insert(2, 25);
	remove(2);

	pop_back();

	// ** 두 번째 노드를 nextNode에 넘겨준다.
	NODE* nextNode = List->next;

	// ** nextNode가 nullptr이 아니라면 반복
	while (nextNode != nullptr)
	{
		// ** 출력
		cout << nextNode->value << endl;

		// ** 다음 노드로 이동
		nextNode = nextNode->next;
	}

	return 0;
}

// 리스트: '효율적'인 추가, 삭제가 가능하다.
#pragma region 0511: class Node
/*
template <typename T>
class Node
{
private:
	Node* next;
	int value;

	Node* end;
public:
	void Push(int value)
	{

		//Node* node = next;

		//while (node != nullptr)
		//	node = node->next;
		//
		//node = new Node;
		//node->value = value;
		//next->next = node;
		//end = node;

		end = new Node;
		end->value = value;
		next = end;

		end = next->next;
	}
public:
	Node() : next(nullptr), value(0), end(next) {}
	~Node() {}
};

int main(void)
{
	// class Node
	Node<int> List;  // Node<int>* List = new Node<int>; List->Push(10);
	List.Push(10);
	List.Push(20);

	return 0;
}
*/
#pragma endregion

#pragma region 0510: if / for / macro function(singleton)
/*
#include <iostream>
#include <Windows.h>
#include <string>
 
// 1. 함수 사용
// 2. 클래스 이해도

// for(초기문; 조건문; 증감문)
// ** 초기문: int i = 0;
// ** 조건문: i < 10;
// ** 증감문: ++i


#define function(x) (cout << x << endl)

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
	Single(Singleton)

//private:
//	static Singleton* Instance;
//public:
//	static Singleton* GetInstance()
//	{
//		if (Instance == nullptr)
//			Instance = new Singleton;
//
//		return Instance;
//	}

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
	//	obj->age = 34;
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



	//function(10);
	//Object* player = new Player;

	//int length = 16;
	//Object* bulletList = new Bullet[length];

	//for (int i = 0; i < length; ++i)
	//{
	//	bulletList->Start(i);
	//
	//	if(bulletList[i].Update(i))
	//		cout << "player age 값이 " << i << "보다 작습니다." << endl;
	//}

	//int value = 10;

	//if (player->Update(value))
	//	cout << "player age 값이 " << value << "보다 작습니다." << endl;

	return 0;
}
*/
#pragma endregion

