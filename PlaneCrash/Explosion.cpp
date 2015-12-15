#include "stdafx.h"
#include "Explosion.h"
#include "resource.h"

CImageList Explosion::mImageList;

Explosion::Explosion(int posX, int posY):ItemBase(posX,posY,0,0),mIndex(0)
{
}

Explosion::~Explosion()
{
}

BOOL Explosion::Draw(CDC * pDC, CRect clientArea)
{
	bool isDrawable = ItemBase::Draw(pDC,clientArea);
	if (isDrawable)
	{
		if (mIndex == 18)
		{
			mIndex = 0;
			return FALSE;
		}

		mImageList.Draw(pDC, mIndex, mPos, ILD_TRANSPARENT);
		mIndex++;
	}
	return isDrawable;
}

BOOL Explosion::loadImage()
{
	return GameObject::loadImage(mImageList, IDB_EXPLOSION, RGB(0, 0, 0), EXPLOSION_HEIGHT, EXPLOSION_HEIGHT, 8);
}
