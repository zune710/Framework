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

	// (매개변수에 없어도 멤버 변수는 다 초기화해 줘야 함)
	
	tagScore() : name(""), Kor(0), Eng(0), Math(0) {}

	tagScore(string _name) : name(_name), Kor(0), Eng(0), Math(0) {}

	tagScore(int _kor, int _eng, int _math)
		: name(""), Kor(_kor), Eng(_eng), Math(_math) {}

	tagScore(string _name, int _kor, int _eng, int _math)
		: name(_name), Kor(_kor), Eng(_eng), Math(_math) {}
} Score;

//Score* score = new Score();  // C에서는 괄호 생략 가능. C#, 자바에서는 괄호 필수.


map<string, list<Score>> StudentList;

Score CreateScore(string _name, int _kor, int _Eng, int _Math);
bool AddStudent(string _key, Score _score);


int main(void)
{
	/*
	map<string, Score> List;

	string key = "홍";
	Score score = Score(10, 20, 30);

	List.insert(make_pair(key, score));

	score = Score(100, 200, 300);
	score.name = "길동";

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
		cout << "국어점수" << " : " << iter->second.Kor << endl;
		cout << "영어점수" << " : " << iter->second.Eng << endl;
		cout << "수학점수" << " : " << iter->second.Math << endl << endl;
	}
	*/


	string key = "홍";  // string key = string("홍"); 와 동일(생성자 생성)
	string name = "길동";

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

Score CreateScore(string _name, int _kor, int _Eng, int _Math)  // 반환형 포인터로 바꿔야 함
{
	// 예외처리들 필요
	
	//Score* score = new Score(_name, _kor, _Eng, _Math);       // 이렇게!

	return Score(_name, _kor, _Eng, _Math);
}

bool AddStudent(string _key, Score _score)
{
	map<string, list<Score>>::iterator iter = StudentList.find(_key);

	if (_score.name == "")  // 점수가 0 미만, 100 초과일 때의 예외처리도 필요
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