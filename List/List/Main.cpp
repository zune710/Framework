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
	/* End ����ϸ� push�� ������ ã�� �ʿ� ����(ū ����� �Ƴ� �� ����)
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
	// ** ����Ʈ�� ��� �� ������ �������� count�� ���� ũ�ٸ�
	// ** ���� �߰��� �� �����Ƿ� ����
	if (Length < count)
		return;

	// ** ����Ʈ�� ����
	NODE* nextNode = List;

	// ** ī��Ʈ�� ����ŭ ���� ���� �̵�
	while (0 < count)
	{
		--count;

		// ** ���� ���� �̵�
		nextNode = nextNode->next;
	}
	// ** �̵��� �����ٸ� ���ο� ��带 �߰�
	
	// ** ���ο� ��� ����
	NODE* newNode = new NODE;
	newNode->next = nullptr;
	newNode->value = value;

	// ** ���� ��带 �ӽ��� ����ҿ� ����
	NODE* tempNode = nextNode->next;

	// ** ���� ��带 �����ϴ� ����ҿ� ���ο� ��带 ��ġ
	nextNode->next = newNode;

	// ** ���ο� ��尡 ����Ű�� ���� ��带 �ӽð����� �ִ� ���� ��ġ
	newNode->next = tempNode;

	++Length;
}

void remove(int count)
{
	// ** ����Ʈ�� ��� �� ������ �������� count�� ���� ũ�ٸ�
	// ** ���� �߰��� �� �����Ƿ� ����
	if (Length < count)
		return;

	// ** ����Ʈ�� ����
	NODE* nextNode = List;

	// ** ī��Ʈ�� ����ŭ ���� ���� �̵�
	while (0 < count)
	{
		--count;

		// ** ���� ���� �̵�
		nextNode = nextNode->next;
	}
	// ** �̵��� �����ٸ� ��带 ����

	// ** �ٴ��� ��带 �ӽ��� ����ҿ� ����
	NODE* tempNode = nextNode->next->next;
	
	// ** ���� ��带 ����
	delete nextNode->next;
	nextNode->next = nullptr;

	// ** ������ ������ �ӽ� �����ߴ� ��带 ����
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
	// a�� b�� ����Ű�� ���� �� c�� �� ���̿� ��� �߰��� ���ΰ�
	int a = 10;
	int b = 20;

	// swap ���
	int temp = a;
	a = b;
	b = temp;

	cout << a << endl;
	cout << b << endl;
	*/
#pragma endregion
#pragma region 0512: pointer, int, stack
	/* 0512
	// ** ������
	int i = 10;  // ������(���� ��)�� ����
	int* n = &i;  // ������(�ּ�)�� ����

	cout << i << endl;  // 10
	cout << *n << endl;  // ����

	cout << &i << endl;  // �ּҰ� ���
	cout << n << endl;  // �ּҰ� ���

	*n = 20;
	cout << i << endl;  // 20


	// ** ������ ���ÿ� int�� �ַ� ���� ����
	cout << sizeof(int*) << endl;  // sizeof(int*)�� x64(64bit)���� 8byte, x86(32bit)���� 4byte 
	// int�� ǥ��(IEEE): short < int <= long
	// int�� ������. PC ȯ�濡 ���� ����� �޶���
	// but int�� size�� x64���� 8byte�� �ƴ� 4byte�� ����: 4byte(����)�� long���� Ŭ �� ���� ����
	
	// 32��Ʈ(x86)���� ��� ������(�ּ�)�� 4����Ʈ�� ǥ����(���� ���� ����. 4����Ʈ������ ��� �ּ� ǥ�� ����)
	// -> int(4byte)�� �� : ������ ���ÿ� int�� �ַ� ���� ����
	cout << sizeof(tagNode*) << endl;
	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(long*) << endl;

	NODE* node = new NODE;  // �� �޸𸮿� ����� 20byte ������(ex. int ���� 5���� ����ü)�� �ּҰ��� �ҷ����� 4byte������ 20byte ������ ��� ����.
	node->next = nullptr;  // (*node).next�� ����

	// �Լ��� �����ͼ� ����Ϸ��� �����ϸ� ��.
	// but �Լ��� �ʿ� �̻��� �Ű����� ����ϸ� ������ ���� �޸� ���� �߻�(��� ���� ��)
	
	// cf. 64��Ʈ(x64)���� ��� ������(�ּ�)�� 8����Ʈ�� ǥ����


	// ** ����
	{
		{
			NODE* node = nullptr;
			{
				NODE* tempNode = new NODE;
				tempNode->next = nullptr;
				tempNode->value = 10;

				node = tempNode;

				cout << tempNode << endl;
			}   // �� ������ �ּҰ� ��
			cout << node << endl;
		}
	}
	*/
#pragma endregion

	// ** ù ��° ���
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

// ����Ʈ: 'ȿ����'�� �߰�, ������ �����ϴ�.
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
#pragma endregion

