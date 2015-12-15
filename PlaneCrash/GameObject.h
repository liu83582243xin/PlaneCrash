#pragma once
#include "afx.h"
class GameObject :
	public CObject
{
public:
	GameObject(int posX = 0,int posY = 0);
	virtual ~GameObject();

	//绘图
	virtual BOOL Draw(CDC *pDC, CRect clientArea) = 0;

	//获取物体矩形
	virtual CRect getRect() = 0;

	//获取坐标
	CPoint getPoint();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	static BOOL loadImage(CImageList& imgList, UINT bmpID, COLORREF crMask, int recX, int recY, int nInitial);
protected:
	//坐标
	CPoint mPos;
	//客户区域
	CRect mClientArea;

	int mOffsetX;
	int mOffsetY;
};

