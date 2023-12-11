#include "ExWindow.h"

ExWindow::ExWindow(int w, int h, int flag)
{
    initgraph(w, h,flag);
    this->w = w;
    this->h = h;
    this->imgURL = "";
}

ExWindow::ExWindow(int w, int h, string imgURL, int flag)
{
    this->imgURL = imgURL;
    this->w = w;
    this->h = h;
    this->img = new IMAGE;
    initgraph(w, h, flag);
    loadimage(this->img, imgURL.c_str(),this->w,this->h);
    putimage(0, 0, this->img);
}

int ExWindow::getWidth() const
{
    return w;
}

int ExWindow::getHeight() const
{
    return h;
}

void ExWindow::reFresh() const
{
    if (this->imgURL.size() == 0) {
        cleardevice();
    }
    else {
        putimage(0, 0, this->img);
    }
}

ExWindow::~ExWindow()
{
    closegraph();
}
