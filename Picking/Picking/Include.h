#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <list>
#include <map>
#include <string>
#include <Windows.h>
#include <math.h>

using namespace std;

#include "Struct.h"
#include "Enum.h"


// ** �̹���
#pragma comment(lib, "msimg32.lib")


#define Single(T)				    \
public:							    \
	static T** GetInstance()	    \
	{							    \
		static T* instance;		    \
		if(instance == nullptr)     \
			instance = new T;       \
		return &instance;		    \
	}							    \
private:						    \
	T(const T&) = delete;		    \
	T& operator=(const T&) = delete;

#define GetSingle(T) (*T::GetInstance())



// ** Ÿ�� ����, ���� ũ��
#define SCALE_X 32.0f
#define SCALE_Y 32.0f

// ** Ÿ�� ����, ���� �ִ� ����
#define COUNT_X 40
#define COUNT_Y 20

// ** ������ â ũ��
#define WIDTH (SCALE_X * COUNT_X)
#define HEIGHT (SCALE_Y * COUNT_Y) + 64

/*
// ** ������ â ũ��
#define WIDTH 1280
#define HEIGHT 640

// ** Ÿ�� ����, ���� �ִ� ����
#define COUNT_X (WIDTH/SCALE_X)
#define COUNT_Y (WIDTH/SCALE_Y)
*/



// ** Ÿ�� �ִ� ����
const int MAX = int(COUNT_X * COUNT_Y);


extern HWND g_hWnd;


template <typename T>
inline void Safe_Release(T& _Object)
{
	if (_Object)
	{
		delete _Object;
		_Object = nullptr;
	}
}