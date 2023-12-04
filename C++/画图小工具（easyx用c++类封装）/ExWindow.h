#pragma once
#include "ExCommon.h"


using namespace std;

class ExWindow
{
public:
	ExWindow(int w=WINDOW_W,int h=WINDOW_H,int flag = 0);
	ExWindow(int w, int h, string imgURL, int flag = 0);

	int getWidth() const;
	int getHeight() const;
	void reFresh() const;
	~ExWindow();

private:
	int w;
	int h;
	IMAGE* img;
	string imgURL;
};
