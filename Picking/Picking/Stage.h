#pragma once
#include "Scene.h"

class Bitmap;
class Object;
class Stage : public Scene
{
private:
	map<string, Bitmap*> ImageList;
	vector<Object*> TileList;
	Object* Restart;
	int Result;
public:
	virtual void Start()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Destroy()override;
public:
	Stage();
	virtual ~Stage();
};

