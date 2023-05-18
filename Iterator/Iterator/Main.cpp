#include <iostream>
#include <list>
#include <map>

using namespace std;


// ** iterator = �ݺ��� = ������ = �ּ�


int main(void)
{
	// 1. iterator ���� ���

	list<int> Numbers;

	Numbers.push_back(100);
	Numbers.push_back(200);

	//cout << *Numbers.begin() << endl;  // 100
	//cout << *Numbers.end() << endl;  // nullptr�̹Ƿ� ���� �߻�

	//Numbers.begin();  // ù ��° ��带 ����Ű�� �ݺ���
	//Numbers.end();  // �������� ����Ű�� �ݺ��� (������ ��� X)

	Numbers.insert(Numbers.begin(), 50);
	Numbers.insert(Numbers.end(), 300);

	list<int>::iterator iter = Numbers.begin();  // 50

	Numbers.insert(iter, 25);

	++iter;  // 25 insert ���� iter�� begin�� �����Ƿ� 50 ��ġ���� ++ �ȴ�.
	++iter;
	++iter;

	Numbers.insert(iter, 250);

	for (list<int>::iterator iter = Numbers.begin(); iter != Numbers.end(); ++iter)
		cout << (*iter) << endl;


	// ==============================================================================
	cout << "====================" << endl;
	// ==============================================================================


	// 2. iterator�� ���� ���

	map<string, int> List;

	List["AAA"] = 10;
	List["BBB"] = 20;
	List["CCC"] = 30;

	/*
	for (int i = 0; i < List.size(); ++i)
		cout << List[i] << endl;  // int�� �ƴϾ ���� �߻� -> iterator ����ؾ� �� 
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

	// ���� �̸��� ���� iterator�� �־ ������ �߻��ϹǷ� ���� ������ �������
	{  
		int* iter = &Array[0];
		cout << (*iter) << endl;  // 1

		cout << *(++iter) << endl;  // 2

		cout << *(iter + 5) << endl;  // 7
		cout << *(iter) << endl;  // 2
	}


	return 0;
}