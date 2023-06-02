#pragma once
#include "Include.h"

class Bitmap;
class Object
{
protected:
	Vector3 position;
	Vector3 scale;
	static map<string, Bitmap*>* m_pImageList;
public:
	static void SetImageList(map<string, Bitmap*>* _ImageList) { m_pImageList = _ImageList; }
public:
	virtual void Start()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Destroy()PURE;
public:
	void SetPosition(const Vector3& _position) { position = _position; }
public:
	Object();
	virtual ~Object();
};

