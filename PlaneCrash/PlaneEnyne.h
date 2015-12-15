#pragma once
#include "PlaneBase.h"
class PlaneEnyne :
	public PlaneBase
{
public:
	PlaneEnyne();
	PlaneEnyne(int posX, int posY);
	~PlaneEnyne();
	BOOL Draw(CDC *pDC, CRect clientArea);
	static BOOL loadImage();
	//BOOL isFirable();
protected:
	void init();
private:
	const static int SIZEWIDTH = 35;
	const static int SIZEHEIGHT = 35;
	static CImageList mImageList;
	//ËÙ¶È
	int mSpeed;
	int mMotion;
	int mVmotion;
	void setRect();
};

