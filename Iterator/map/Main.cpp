#include <iostream>
#include <map>
#include <list>

using namespace std;


typedef struct Score
{
	string name;
	int Kor;
	int Eng;
	int Math;

	Score() : Kor(0), Eng(0), Math(0) {}

	Score(int _kor, int _eng, int _math)
		: Kor(_kor), Eng(_eng), Math(_math) {}

	//int operator<<() {}
};


int main(void)
{
	/*
	map<string, int> List;

	List.insert(make_pair("AAA", 100));
	List["AAA"] = 10;  // "AAA"�� 2�� ����� ���� �ƴ϶� ���� 100���� 10���� ����� ��
					   // -> "AAA"��� �̸��� ���� ���� 2���� �� ����.

	cout << List["AAA"] << endl;  // 10
	*/

	/*
	map<string, Score> List;

	string name = "ȫ�浿";
	Score score = Score(10, 20, 30);

	List.insert(make_pair(name, score));

	score = Score(100, 200, 300);
	List[name] = score;

	cout << List[name].Kor << endl;
	cout << List[name].Eng << endl;
	cout << List[name].Math << endl;
	// ������ �̸��� ���� �� �־ �̷��� ���� ���� -> multimap ����ϸ� ��

	multimap<string, Score> multiList;

	multiList.insert(make_pair(name, score));
	multiList.insert(make_pair(name, score));

	for (multimap<string, Score>::iterator iter = multiList.begin(); iter != multiList.end(); ++iter)
	{
		cout << "[" << iter->first << "]" << endl;
		cout << "��������" << " : " << iter->second.Kor << endl;
		cout << "��������" << " : " << iter->second.Eng << endl;
		cout << "��������" << " : " << iter->second.Math << endl << endl;
		// cout << iter->first << " : " << iter->second << endl; �̷��� ������ ����ü�� operator<< �����ε� ������ ��
	}
	// multimap ���� ȫ�浿�� 2�� ���� �� ����
	// ������ �̸��� �������� �ƴϱ� ������(������ �̸� ���� �� �ֱ� ������) key�� �̸����� ���� ����
	// ����ü�� string name ���� �߰��ؼ� �����
	*/

	// multimap�� ���� ���°�

	// map: Ʈ������ ���� - ������ ã�� �� ������ ������ ������ ��(������ �������� �� ����)
	// multimap: ����Ʈ?

	/*
	map<string, Score> List;

	string key = "ȫ";
	Score score = Score(10, 20, 30);

	List.insert(make_pair(key, score));

	score = Score(100, 200, 300);
	score.name = "�浿";

	List[key] = score;

	cout << key + List[key].name << endl;
	cout << List[key].Kor << endl;
	cout << List[key].Eng << endl;
	cout << List[key].Math << endl;
	*/
	// ȫ�̶� ���� ���� ����� ���� ���� �� �����Ƿ� list�� ����Ѵ�.

	map<string, list<Score>> StudentList;

	string key = "ȫ";
	Score score = Score(10, 20, 30);
	score.name = "�浿";

	Score score2 = Score(100, 200, 300);
	score2.name = "�浿";

	list<Score> List;
	List.push_back(score);
	List.push_back(score2);

	StudentList.insert(make_pair(key, List));

	for (list<Score>::iterator iter = List.begin(); iter != List.end(); ++iter)
	{
		cout << "[" << key + iter->name << "]" << endl;
		cout << "��������" << " : " << iter->Kor << endl;
		cout << "��������" << " : " << iter->Eng << endl;
		cout << "��������" << " : " << iter->Math << endl << endl;
	}

	return 0;
}

map<string, list<Score>> TestList;
void AddStudent(string key, Score score)
{

	map<string, list<Score>>::iterator iter = TestList.find(key);
	if (iter == TestList.end())
	{
		list<Score> tempList;
		tempList.push_back(score);

		TestList.insert(make_pair(key, tempList));
	}
	else
		iter->second.push_back(score);
}

list<Score>* GetList(const string& key)
{
	map<string, list<Score>>::iterator iter = TestList.find(key);

	if (iter == TestList.end())
		return nullptr;
	else
		return &iter->second;
}