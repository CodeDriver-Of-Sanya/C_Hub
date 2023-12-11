#pragma once
#include"ExCommon.h"
#include"ExPoint.h"
class ExLine
{
public:
	ExLine(int size = 5, COLORREF color = BLACK);
	void draw(ExMessage msg);
	void setSize(int& size);
	void setColor(COLORREF color);
private:
	//线的粗细
	int size;
	//线的颜色
	COLORREF color;
	//鼠标按键是否按下
	bool isDown;
	//线的起点
	ExPoint begin;
};

