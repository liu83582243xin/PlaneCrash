#include "stdafx.h"
#include "PlaneBoss.h"
#include "resource.h"

CImageList PlaneBoss::mImageList;

PlaneBoss::PlaneBoss()
{
	init();
}

PlaneBoss::PlaneBoss(int posX, int posY) : PlaneBase(posX, posY)
{
	init();
}

BOOL PlaneBoss::Draw(CDC * pDC, CRect clientArea)
{
	BOOL isDrawable = PlaneBase::Draw(pDC,clientArea);
	if (isDrawable)
	{
		mDelayedTime++;
		if (mDelayedTime>10)
			mDelayedTime = 0;
		mPos.y = mPos.y + mMotion * mSpeed / 2;

		mPos.x = mPos.x + mHotion *mSpeed / 2;
		if (mPos.y > GAME_CLIENT_HEIGHT + mPlaneHeight)
			return FALSE;
		if (mPos.y < -mPlaneHeight)
			return FALSE;
		if (mPos.x >= GAME_CLIENT_WIDTH - mPlaneWidth + 20)
		{
			mHotion = -mHotion;
		}
		if (mPos.x <= -5)
		{
			mHotion = -mHotion;
		}
		if (mPos.y <= -5)
		{
			mMotion = -mMotion;
		}
		if (mPos.y >= (GAME_CLIENT_HEIGHT - mPlaneHeight) / 3 + 20)
		{
			mMotion = -mMotion;
		}

		mImageList.Draw(pDC, 0, mPos, ILD_TRANSPARENT);
	}
	return isDrawable;

}

BOOL PlaneBoss::loadImage()
{
	return GameObject::loadImage(mImageList, IDB_BOSS, RGB(255, 255, 255), SIZEWIDTH, SIZEHEIGHT, 1);
}


PlaneBoss::~PlaneBoss()
{
}

void PlaneBoss::init()
{
	PlaneBase::init();
	setRect();

	mPos.x = rand() % (GAME_CLIENT_WIDTH - mPlaneWidth) + 1;
	mPos.y = 10;

	mMotion = 1;
	mHotion = 1;
	mSpeed = 2;
	mDelayedTime = 0;
	mBlood = 30;
	mScore = 500;
}

void PlaneBoss::setRect()
{
	mPlaneWidth = SIZEWIDTH;
	mPlaneHeight = SIZEHEIGHT;
}
