#include <iostream>
#include <map>
#include <list>

using namespace std;


typedef struct tagScore
{
	string name;
	int Kor;
	int Eng;
	int Math;

	// (�Ű������� ��� ��� ������ �� �ʱ�ȭ�� ��� ��)
	
	tagScore() : name(""), Kor(0), Eng(0), Math(0) {}

	tagScore(string _name) : name(_name), Kor(0), Eng(0), Math(0) {}

	tagScore(int _kor, int _eng, int _math)
		: name(""), Kor(_kor), Eng(_eng), Math(_math) {}

	tagScore(string _name, int _kor, int _eng, int _math)
		: name(_name), Kor(_kor), Eng(_eng), Math(_math) {}
} Score;

//Score* score = new Score();  // C������ ��ȣ ���� ����. C#, �ڹٿ����� ��ȣ �ʼ�.


map<string, list<Score>> StudentList;

Score CreateScore(string _name, int _kor, int _Eng, int _Math);
bool AddStudent(string _key, Score _score);


int main(void)
{
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

	multimap<string, Score> multiList;

	multiList.insert(make_pair(key, score));
	multiList.insert(make_pair(key, score));


	for (multimap<string, Score>::iterator iter = multiList.begin(); iter != multiList.end(); ++iter)
	{
		cout << "[" << iter->first << "]" << endl;
		cout << "��������" << " : " << iter->second.Kor << endl;
		cout << "��������" << " : " << iter->second.Eng << endl;
		cout << "��������" << " : " << iter->second.Math << endl << endl;
	}
	*/


	string key = "ȫ";  // string key = string("ȫ"); �� ����(������ ����)
	string name = "�浿";

	Score score = CreateScore(name, 10, 20, 30);

	if (!AddStudent(key, score))
		cout << "Log" << endl;

	for (map<string, list<Score>>::iterator iter = StudentList.begin();
		iter != StudentList.end(); ++iter)
	{
		for (list<Score>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			cout << iter2->name << endl;
			cout << iter2->Kor << endl;
			cout << iter2->Eng << endl;
			cout << iter2->Math << endl << endl;
		}
	}
	
	return 0;
}

Score CreateScore(string _name, int _kor, int _Eng, int _Math)  // ��ȯ�� �����ͷ� �ٲ�� ��
{
	// ����ó���� �ʿ�
	
	//Score* score = new Score(_name, _kor, _Eng, _Math);       // �̷���!

	return Score(_name, _kor, _Eng, _Math);
}

bool AddStudent(string _key, Score _score)
{
	map<string, list<Score>>::iterator iter = StudentList.find(_key);

	if (_score.name == "")  // ������ 0 �̸�, 100 �ʰ��� ���� ����ó���� �ʿ�
		return false;


	if (iter == StudentList.end())
	{
		list<Score> tempList;
		tempList.push_back(_score);
		StudentList.insert(make_pair(_key, tempList));
	}
	else
		iter->second.push_back(_score);
	
	return true;
}