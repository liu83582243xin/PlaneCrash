#pragma once
#include "PlaneBase.h"
class PlanePlayer :
	public PlaneBase
{
public:
	PlanePlayer();

	PlanePlayer(int posX, int posY);

	void moveDown();
	void moveUp();
	BOOL Draw(CDC *pDC, CRect clientArea);
	~PlanePlayer();
protected:
	void init();

private:
	const static int SIZEWIDTH = 40;
	const static int SIZEHEIGHT = 60;
	void setRect();
};

