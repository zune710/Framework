#include <iostream>
#include <list>
#include <map>

using namespace std;


// ** iterator = 반복자 = 포인터 = 주소


int main(void)
{
	// 1. iterator 쓰는 방법

	list<int> Numbers;

	Numbers.push_back(100);
	Numbers.push_back(200);

	//cout << *Numbers.begin() << endl;  // 100
	//cout << *Numbers.end() << endl;  // nullptr이므로 오류 발생

	//Numbers.begin();  // 첫 번째 노드를 가리키는 반복자
	//Numbers.end();  // 마지막을 가리키는 반복자 (마지막 노드 X)

	Numbers.insert(Numbers.begin(), 50);
	Numbers.insert(Numbers.end(), 300);

	list<int>::iterator iter = Numbers.begin();  // 50

	Numbers.insert(iter, 25);

	++iter;  // 25 insert 전에 iter에 begin을 줬으므로 50 위치부터 ++ 된다.
	++iter;
	++iter;

	Numbers.insert(iter, 250);

	for (list<int>::iterator iter = Numbers.begin(); iter != Numbers.end(); ++iter)
		cout << (*iter) << endl;


	// ==============================================================================
	cout << "====================" << endl;
	// ==============================================================================


	// 2. iterator를 쓰는 경우

	map<string, int> List;

	List["AAA"] = 10;
	List["BBB"] = 20;
	List["CCC"] = 30;

	/*
	for (int i = 0; i < List.size(); ++i)
		cout << List[i] << endl;  // int가 아니어서 오류 발생 -> iterator 사용해야 함 
	*/

	for (map<string, int>::iterator iter = List.begin(); iter != List.end(); ++iter)
		cout << iter->first << " : " << (*iter).second << endl;


	// ==============================================================================
	cout << "====================" << endl;
	// ==============================================================================

	// 3.

	const int size = 16;
	int Array[16] = { 1, 2, 3, 4, 5, 6, 7 };

	for (int i = 0; i < size; ++i)
		cout << Array[i] << endl;

	cout << "--------------------" << endl;

	// 위에 이름이 같은 iterator가 있어서 오류가 발생하므로 지역 변수로 만들어줌
	{  
		int* iter = &Array[0];
		cout << (*iter) << endl;  // 1

		cout << *(++iter) << endl;  // 2

		cout << *(iter + 5) << endl;  // 7
		cout << *(iter) << endl;  // 2
	}


	return 0;
}