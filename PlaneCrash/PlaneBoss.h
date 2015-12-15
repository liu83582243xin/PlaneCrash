#pragma once
#include "PlaneBase.h"
class PlaneBoss :
	public PlaneBase
{
public:
	PlaneBoss();
	PlaneBoss(int posX, int posY);
	BOOL Draw(CDC *pDC, CRect clientArea);
	static BOOL loadImage();
	const static int level = 300;
	~PlaneBoss();
protected:
	void init();
private:
	const static int SIZEWIDTH = 197;
	const static int SIZEHEIGHT = 134;
	static CImageList mImageList;
	//ÀŸ∂»
	int mSpeed;
	//—” ±
	void setRect();
};

