#pragma once
class Plane
{
protected:
	int offsetX;
	int offsetY;
	int offset;
	int sizeWidth;
	int sizeHeight;
	CRect *client;
public:
	Plane();
	void Draw(CDC *pDc, CRect *client);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	~Plane();
};

