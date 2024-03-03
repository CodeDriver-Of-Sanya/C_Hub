#pragma once
#include"ExCommon.h"
class ExPoint
{
public:
	ExPoint(int x=-1,int y=-1);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	ExPoint getPos();
	void setPos(int x, int y);

private:
	int x;
	int y;
};
