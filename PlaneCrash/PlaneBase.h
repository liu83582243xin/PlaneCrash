#pragma once
#include "GameObject.h"
class PlaneBase :
	public GameObject
{
public:
	int mScore;

public:
	PlaneBase();
	PlaneBase(int posX, int posY);

	void moveLeft();
	void moveRight();
	int getMotion();
	int getHtion();
	int getVmotion();
	int mBlood;
	CRect getRect();
	BOOL isFirable();

	BOOL Draw(CDC *pDC, CRect clientArea);

	~PlaneBase();

protected:
	int mPlaneWidth;
	int mPlaneHeight;
	int mMotion;
	int mHotion;
	int mVmotion;
	int mDelayedTime;

protected:
	void init();
};

