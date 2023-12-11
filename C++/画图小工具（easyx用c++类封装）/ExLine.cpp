#include "ExLine.h"

ExLine::ExLine(int size, COLORREF color)
{
	this->size = size;
	this->color = color;
	this->isDown = false;
}

void ExLine::draw(ExMessage msg)
{
	//左键按下
	if (msg.message == WM_LBUTTONDOWN) {
		this->isDown = true;
		//记录起点
		this->begin = ExPoint(msg.x, msg.y);
	}
	//左键弹起
	if (msg.message == WM_LBUTTONUP) {
		this->isDown = false;
	}
	//画线：左键按下+移动
	if (this->isDown == true && msg.message == WM_MOUSEMOVE) {
		setlinestyle(PS_ENDCAP_ROUND,this->size);
		setlinecolor(this->color);
		line(this->begin.getX(), this->begin.getY(), msg.x, msg.y);
	}
	//这一次画线的结尾是下一次画线的起点
	this->begin = ExPoint(msg.x, msg.y);
}

void ExLine::setSize(int& size)
{
	this->size = size;
}

void ExLine::setColor(COLORREF color)
{
	this->color = color;
}
