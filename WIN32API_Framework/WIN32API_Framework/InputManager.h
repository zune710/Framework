#pragma once
#include "Include.h"

class InputManager
{
public:
	Single(InputManager)

private:
	DWORD inputKey;
public:
	DWORD GetKey() { return inputKey; }

	void CheckKey();
private:
	InputManager();
public:
	~InputManager();
};
