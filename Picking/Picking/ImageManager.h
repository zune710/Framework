#pragma once
#include "Include.h"

class Bitmap;
class ImageManager
{
private:
	static ImageManager* instance;
public:
	static ImageManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new ImageManager;
		return instance;
	}
private:
	map<string, Bitmap*> m_ImageList;
public:
	map<string, Bitmap*>* GetList() { return &m_ImageList; }
private:
	ImageManager();
public:
	~ImageManager();
};

