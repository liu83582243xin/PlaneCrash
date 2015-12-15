#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(int posX, int posY) : mPos(posX,posY)
{
	mOffsetX = 10;
	mOffsetY = 10;
}

CPoint GameObject::getPoint()
{
	return mPos;
}

void GameObject::moveUp()
{
	mPos.y -= mOffsetY;
}

void GameObject::moveDown()
{
	mPos.y += mOffsetY;
}

void GameObject::moveLeft()
{
	mPos.x -= mOffsetX;
}

void GameObject::moveRight()
{
	mPos.x += mOffsetX;
}

BOOL GameObject::loadImage(CImageList & imgList, UINT bmpID, COLORREF crMask, int recX, int recY, int nInitial)
{
	CBitmap bmp;
	if (!bmp.LoadBitmap(bmpID))
		return FALSE;

	if (!imgList.Create(recX, recY, ILC_COLOR24 | ILC_MASK, nInitial, 0))
		return FALSE;

	imgList.Add(&bmp, crMask);

	return TRUE;
}

GameObject::~GameObject()
{
}
