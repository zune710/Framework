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
	List["AAA"] = 10;  // "AAA"가 2개 생기는 것이 아니라 값이 100에서 10으로 변경된 것
					   // -> "AAA"라는 이름을 가진 값은 2개일 수 없다.

	cout << List["AAA"] << endl;  // 10
	*/

	/*
	map<string, Score> List;

	string name = "홍길동";
	Score score = Score(10, 20, 30);

	List.insert(make_pair(name, score));

	score = Score(100, 200, 300);
	List[name] = score;

	cout << List[name].Kor << endl;
	cout << List[name].Eng << endl;
	cout << List[name].Math << endl;
	// 동일한 이름이 있을 수 있어서 이렇게 쓰지 않음 -> multimap 사용하면 됨

	multimap<string, Score> multiList;

	multiList.insert(make_pair(name, score));
	multiList.insert(make_pair(name, score));

	for (multimap<string, Score>::iterator iter = multiList.begin(); iter != multiList.end(); ++iter)
	{
		cout << "[" << iter->first << "]" << endl;
		cout << "국어점수" << " : " << iter->second.Kor << endl;
		cout << "영어점수" << " : " << iter->second.Eng << endl;
		cout << "수학점수" << " : " << iter->second.Math << endl << endl;
		// cout << iter->first << " : " << iter->second << endl; 이렇게 쓰려면 구조체에 operator<< 오버로딩 만들어야 함
	}
	// multimap 쓰면 홍길동을 2개 가질 수 있음
	// 하지만 이름은 고유값이 아니기 때문에(동일한 이름 있을 수 있기 때문에) key를 이름으로 쓰지 않음
	// 구조체에 string name 변수 추가해서 사용함
	*/

	// multimap은 언제 쓰는가

	// map: 트리구조 형태 - 빠르게 찾을 수 있으나 느리게 삽입이 됨(개수가 많을수록 더 느림)
	// multimap: 리스트?

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
	*/
	// 홍이란 성을 가진 사람이 여러 명일 수 있으므로 list를 사용한다.

	map<string, list<Score>> StudentList;

	string key = "홍";
	Score score = Score(10, 20, 30);
	score.name = "길동";

	Score score2 = Score(100, 200, 300);
	score2.name = "길동";

	list<Score> List;
	List.push_back(score);
	List.push_back(score2);

	StudentList.insert(make_pair(key, List));

	for (list<Score>::iterator iter = List.begin(); iter != List.end(); ++iter)
	{
		cout << "[" << key + iter->name << "]" << endl;
		cout << "국어점수" << " : " << iter->Kor << endl;
		cout << "영어점수" << " : " << iter->Eng << endl;
		cout << "수학점수" << " : " << iter->Math << endl << endl;
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