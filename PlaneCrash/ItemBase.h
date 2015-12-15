#pragma once
#include "GameObject.h"
class ItemBase :
	public GameObject
{
public:
	ItemBase(int posX, int posY, int motion, int hotion);
	BOOL Draw(CDC* pDC, CRect clientArea);
	CRect getRect();

	~ItemBase();

protected:
	int    mMotion;
	int    mHotion;
	int mItemWidth;
	int mItemHeight;

protected:
	void setRect(int width, int height);

};

