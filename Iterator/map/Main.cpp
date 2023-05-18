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

	map<string, list<Score>> StudentList;

	string key = "홍";
	Score score = Score(10, 20, 30);
	score.name = "길동";

	Score score2 = Score(100, 200, 300);
	score2.name = "동길";

	
	list<Score> List;
	List.push_back(score);
	List.push_back(score2);
	
	StudentList.insert(make_pair(key, List));
	StudentList.insert(make_pair("김", List));
	
	for (map<string, list<Score>>::iterator iter1 = StudentList.begin(); iter1 != StudentList.end(); ++iter1)
	{	
		for (list<Score>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); ++iter2)
		{
			cout << "[" << iter1->first + iter2->name << "]" << endl;
			cout << "국어점수" << " : " << iter2->Kor << endl;
			cout << "영어점수" << " : " << iter2->Eng << endl;
			cout << "수학점수" << " : " << iter2->Math << endl << endl;
		}
	}
	

	return 0;
}