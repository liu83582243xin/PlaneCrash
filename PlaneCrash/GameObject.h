#pragma once
#include "afx.h"
class GameObject :
	public CObject
{
public:
	GameObject(int posX = 0,int posY = 0);
	virtual ~GameObject();

	//��ͼ
	virtual BOOL Draw(CDC *pDC, CRect clientArea) = 0;

	//��ȡ�������
	virtual CRect getRect() = 0;

	//��ȡ����
	CPoint getPoint();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	static BOOL loadImage(CImageList& imgList, UINT bmpID, COLORREF crMask, int recX, int recY, int nInitial);
protected:
	//����
	CPoint mPos;
	//�ͻ�����
	CRect mClientArea;

	int mOffsetX;
	int mOffsetY;
};

