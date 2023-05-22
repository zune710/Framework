#pragma once
#include "Include.h"

class GameObject;
class Prototype
{
public:
	Single(Prototype)
private:
	map<string, GameObject*> PrototypeObject;
public:
	void Start();
	GameObject* GetGameObject(string _key);
private:
	Prototype();
public:
	~Prototype();
};

