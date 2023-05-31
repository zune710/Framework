#include "GameObject.h"

map<string, Bitmap*>* GameObject::m_ImageList = nullptr;

GameObject::GameObject() : Speed(0.0f), HP(0), pBridge(nullptr), Time(0), frame({ 0, })
{

}

GameObject::~GameObject()
{

}
