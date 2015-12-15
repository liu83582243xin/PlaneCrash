#include "stdafx.h"
#include "Bomb.h"
#include "resource.h"

CImageList Bomb::mImageList;

Bomb::Bomb(int posX, int posY, int motion, int hotion):ItemBase(posX, posY, motion, hotion)
{
	mItemWidth = SIZEWIDTH;
	mItemHeight = SIZEHEIGHT;
}

BOOL Bomb::Draw(CDC * pDC, CRect clientArea)
{
	bool isDrawable = ItemBase::Draw(pDC,clientArea);
	if (isDrawable)
	{
			mPos.y = mPos.y + mMotion * 8;
			mPos.x = mPos.x + mHotion * 4;

		if (mPos.y < -mItemHeight)
			return FALSE;

		mImageList.Draw(pDC, 0, mPos, ILD_TRANSPARENT);
	}
	return isDrawable;
}

BOOL Bomb::loadImage()
{
	return GameObject::loadImage(mImageList, IDB_BOMB, RGB(0, 0, 0), SIZEWIDTH, SIZEHEIGHT, 1);
}

Bomb::~Bomb()
{
}
