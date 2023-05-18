#include <iostream>
#include <vector>

using namespace std;


int* Numbers;
int Size;
int Capacity;


void erase(int _where)
{
	if (_where > Size || _where <= 0)
		return;

	--Size;
	--_where;

	for (int i = _where; i < Size; ++i)
		Numbers[i] = Numbers[i + 1];
}

/*
void erase(int _where)
{
	if (_where > Size || _where <= 0)
		return;

	_where -= 1;

	for (int i = _where; i < Size - 1; ++i)
		Numbers[i] = Numbers[i + 1];

	--Size;
}
*/

void insert(int _where, int _value)
{
	if (_where > Size || _where <= 0)
		return;

	if (Size == Capacity)
	{
		int Length = int(Capacity * 0.5f);
		Capacity += Length < 1 ? 1 : Length;
	}

	_where -= 1;

	for (int i = Size; _where <= i; --i) // Size - 1?
		Numbers[i + 1] = Numbers[i];

	Numbers[_where] = _value;
	++Size;
}


// 위치가 사이즈보다 크면 X
// 사이즈가 수용량보다 크면 X
/*
void insert(int _where, int _value)
{
	if (_where > Size)
		return;

	if (Size == Capacity)
	{
		int Length = int(Capacity * 0.5f);
		Capacity += Length < 1 ? 1 : Length;
	}

	int* temp = new int[Capacity];

	++Size;

	for (int i = 0; i < _where; ++i)
		temp[i] = Numbers[i];

	temp[_where] = _value;

	for (int i = _where + 1; i < Size; ++i)
		temp[i] = Numbers[i - 1];

	delete Numbers;
	Numbers = nullptr;

	Numbers = temp;
}
*/

void pop_back()
{
	if (Size != 0)
		--Size;
}

void push_back(int _value)
{
	if (Size == Capacity)
	{
		int Length = int(Capacity * 0.5f);
		Capacity += Length < 1 ? 1 : Length;
	}

	int* temp = new int[Capacity];

	for (int i = 0; i < Size; ++i)
		temp[i] = Numbers[i];

	delete Numbers;
	Numbers = nullptr;

	Numbers = temp;

	Numbers[Size] = _value;

	++Size;
}


int main(void)
{
	for (int i = 0; i < 10; ++i)
	{
		push_back(i * 10 + 10);
		cout << "size: " << Size << endl;
		cout << "capacity: " << Capacity << endl << endl;
	}

	//pop_back();

	insert(6, 55);

	erase(6);

	for (int i = 0; i < Size; ++i)
		cout << Numbers[i] << endl;

	return 0;
}