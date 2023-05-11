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
	// ** ù ��° ���
	// create
	List = new NODE;

	// initialize
	List->next = nullptr;
	List->value = 0;

	//=======================================
	// ** �� ��° ���
	// create
	List->next = new NODE;

	// initialize
	List->next->next = nullptr;
	List->next->value = 10;

	//=======================================
	// ** �� ��° ���
	// create
	List->next->next = new NODE;

	// initialize
	List->next->next->next = nullptr;
	List->next->next->value = 20;

	//=======================================
	// ** �� ��° ���
	// create
	List->next->next->next = new NODE;

	// initialize
	List->next->next->next->next = nullptr;
	List->next->next->next->value = 30;


	// ** �� ��° ��带 nextNode�� �Ѱ��ش�.
	NODE* nextNode = List->next;

	// ** nextNode�� nullptr�� �ƴ϶�� �ݺ�
	while (nextNode != nullptr)
	{
		// ** ���
		cout << nextNode->value << endl;

		// ** ���� ���� �̵�
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
// 1. �Լ� ���
// 2. Ŭ���� ���ص�

// for(�ʱ⹮; ���ǹ�; ������)
// ** �ʱ⹮: int i = 0;
// ** ���ǹ�: i < 10;
// ** ������: ++i


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
	//		cout << "player age ���� " << i << "���� �۽��ϴ�." << endl;
	//}

	//int value = 10;

	//if (player->Update(value))
	//	cout << "player age ���� " << value << "���� �۽��ϴ�." << endl;

	return 0;
}
*/
