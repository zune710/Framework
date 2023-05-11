#include <iostream>

using namespace std;

typedef struct tagNode
{
	tagNode* next;
	int value;
} NODE;

NODE* List;
int Length;

void push(int value)
{
	NODE* nextNode = List;

	while (nextNode->next != nullptr)
		nextNode = nextNode->next;

	// create
	nextNode->next = new NODE;

	// initialize
	nextNode->next->next = nullptr;
	nextNode->next->value = value;

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
}

void erase(int count)
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

	NODE* tempNode = nextNode->next;

	nextNode->next = tempNode->next;

	delete tempNode;
	tempNode = nullptr;
}

int main(void)
{
	/*
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
	
	
	// ** 첫 번째 노드
	// create
	List = new NODE;

	// initialize
	List->next = nullptr;
	List->value = 0;

	//=======================================
	push(10);
	push(20);
	push(30);
	push(40);

	insert(2, 25);
	erase(2);

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

