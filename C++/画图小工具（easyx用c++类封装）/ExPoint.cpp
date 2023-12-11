#include "ExPoint.h"

ExPoint::ExPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

int ExPoint::getX()
{
	return this->x;
}

void ExPoint::setX(int x)
{
	this->x = x;
}

int ExPoint::getY()
{
	return this->y;
}

void ExPoint::setY(int y)
{
	this->y = y;
}

ExPoint ExPoint::getPos()
{
	return *this;
}

void ExPoint::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}
