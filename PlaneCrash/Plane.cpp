#include "stdafx.h"
#include "Plane.h"
#include "resource.h"


Plane::Plane()
{
	this->offsetX = 100;
	this->offsetY = 100;
	this->offset = 10;
	this->sizeWidth = 50;
	this->sizeHeight = 60;
}

void Plane::Draw(CDC *pDc, CRect *client)
{
	this->client = client;

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_ME);

	CImageList imageList;
	imageList.Create(sizeWidth, sizeHeight, ILC_COLOR8 | ILC_MASK, 1, 0);
	imageList.Add(&bitmap, RGB(0, 0, 0));
	imageList.Draw(pDc, 0, CPoint(this->offsetX, this->offsetY), ILD_NORMAL);
}

void Plane::moveDown()
{
	//if (this->offsetY < (this->client)->Height - offset)
	//{
		this->offsetY += offset;
	//}
}

void Plane::moveUp()
{
	//if (this->offsetY > offset)
	//{
		this->offsetY -= offset;
	//}
}

void Plane::moveRight()
{
	if (offsetX < client->Width() - offset - sizeWidth)
	{
		this->offsetX += offset;
	}
}

void Plane::moveLeft()
{
	if (this->offsetX > offset)
	{
		this->offsetX -= offset;
	}
}

Plane::~Plane()
{
}
