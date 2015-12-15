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
	//炸弹的图片列表
	static CImageList mImageList;
	//图像索引的步进计数
	int   mIndex;
public:
	static const int  EXPLOSION_WIDTH = 66;
	static const int  EXPLOSION_HEIGHT = 66;
};

