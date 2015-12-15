#include "stdafx.h"
#include "PlaneBase.h"


PlaneBase::PlaneBase():mPlaneWidth(0),mPlaneHeight(0),mMotion(0),mHotion(0),mVmotion(0),mBlood(0),mDelayedTime(0)
{
	mBlood = 10;
}

PlaneBase::PlaneBase(int posX, int posY) : GameObject(posX, posY),mPlaneWidth(0),mPlaneHeight(0),mMotion(0),mHotion(0),mVmotion(0),mBlood(0),mDelayedTime(0)
{
	mBlood = 10;
}

void PlaneBase::moveLeft()
{
	if (mPos.x > mOffsetX)
	{
		GameObject::moveLeft();
	}
}

void PlaneBase::moveRight()
{
	if (mPos.x < mClientArea.Width() - mOffsetX - mPlaneWidth)
	{
		GameObject::moveRight();
	}
}

int PlaneBase::getMotion()
{
	return mMotion;
}

int PlaneBase::getHtion()
{
	return mHotion;
}

int PlaneBase::getVmotion()
{
	return mVmotion;
}

BOOL PlaneBase::isFirable()
{
	return mDelayedTime == 0;
}

BOOL PlaneBase::Draw(CDC * pDC, CRect clientArea)
{
	this->mClientArea = clientArea;

	return true;
}

CRect PlaneBase::getRect()
{
	return CRect(mPos, CPoint(mPos.x + mPlaneWidth, mPos.y + mPlaneHeight));
}

void PlaneBase::init()
{
	mBlood = 10;
}

PlaneBase::~PlaneBase()
{
}
