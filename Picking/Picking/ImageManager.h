#pragma once
#include "Include.h"

class Bitmap;
class ImageManager
{
public:
	Single(ImageManager)
private:
	map<string, Bitmap*> m_ImageList;
public:
	map<string, Bitmap*>* GetList() { return &m_ImageList; }
private:
	ImageManager();
public:
	~ImageManager();
};

