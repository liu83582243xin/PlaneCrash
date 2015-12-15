#pragma once
#include "ItemBase.h"
class Ball :
	public ItemBase
{
public:
	Ball(int posX, int posY, int motion, int hotion);
	BOOL Draw(CDC* pDC, CRect clientArea);

	static BOOL loadImage();
	~Ball();
private:
	const static int SIZEWIDTH = 8;
	const static int SIZEHEIGHT = 8;
	static CImageList mImageList;
};

