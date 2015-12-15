#pragma once
#include "afx.h"
#include "ItemBase.h"
class Explosion :
	public ItemBase
{
public:
	Explosion(int posX, int posY);
	~Explosion();
	BOOL Draw(CDC* pDC, CRect clientArea);

	static BOOL loadImage();
private:
	//ը����ͼƬ�б�
	static CImageList mImageList;
	//ͼ�������Ĳ�������
	int   mIndex;
public:
	static const int  EXPLOSION_WIDTH = 66;
	static const int  EXPLOSION_HEIGHT = 66;
};

