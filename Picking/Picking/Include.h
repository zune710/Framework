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


// ** 이미지
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



// ** 타일 가로, 세로 크기
#define SCALE_X 32.0f
#define SCALE_Y 32.0f

// ** 타일 가로, 세로 최대 개수
#define COUNT_X 40
#define COUNT_Y 20

// ** 윈도우 창 크기
#define WIDTH (SCALE_X * COUNT_X)
#define HEIGHT (SCALE_Y * COUNT_Y) + 64

/*
// ** 윈도우 창 크기
#define WIDTH 1280
#define HEIGHT 640

// ** 타일 가로, 세로 최대 개수
#define COUNT_X (WIDTH/SCALE_X)
#define COUNT_Y (WIDTH/SCALE_Y)
*/



// ** 타일 최대 개수
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