#include <iostream>
#include <Windows.h> // 0510
#include <string> // 0510

using namespace std;

typedef struct tagNode
{
	tagNode* next;
	int value;
} NODE;

NODE* List;

void Push(int value);

int main(void)
{
	// ** 첫 번째 노드
	// create
	List = new NODE;

	// initialize
	List->next = nullptr;
	List->value = 0;

	//=======================================
	// ** 두 번째 노드
	// create
	List->next = new NODE;

	// initialize
	List->next->next = nullptr;
	List->next->value = 10;

	//=======================================
	// ** 세 번째 노드
	// create
	List->next->next = new NODE;

	// initialize
	List->next->next->next = nullptr;
	List->next->next->value = 20;

	//=======================================
	// ** 네 번째 노드
	// create
	List->next->next->next = new NODE;

	// initialize
	List->next->next->next->next = nullptr;
	List->next->next->next->value = 30;


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

void Push(int value)
{
	NODE* nextNode = List;

	while (nextNode != nullptr)
		nextNode = nextNode->next;

	nextNode = new NODE;

	nextNode->value = value;
	nextNode->next = nullptr;
}



// class Node
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



// 0510
/*
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
