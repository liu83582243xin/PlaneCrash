#pragma once
#include "ItemBase.h"
class Bomb :
	public ItemBase
{
public:
	Bomb(int posX, int posY, int motion, int hotion);
	BOOL Draw(CDC* pDC, CRect clientArea);

	static BOOL loadImage();
	~Bomb();

private:
	const static int SIZEWIDTH = 10;
	const static int SIZEHEIGHT = 20;
	static CImageList mImageList;
};

