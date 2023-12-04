#include "Res.h"

map<string, IMAGE*> Res::layout;
map<string, pair<int, IMAGE*>> Res::action;

Res::~Res()
{
}

Res* Res::GetRes()
{
	static Res* res = new Res;
	return res;
}

void Res::ShowLayout(int x, int y, string name)
{
	putimage(x, y, GetRes()->layout[name]);
}

void Res::ShowAction(int x, int y, string name, int frame)
{
	putimage(x, y,400,300, GetRes()->action[name].second+0,frame*400,0,SRCAND);
	putimage(x, y,400,300, GetRes()->action[name].second+1,frame*400,0,SRCPAINT);
}

Res::Res()
{
	
	layout["±³¾°"] = new IMAGE;
	loadimage(layout["±³¾°"],"./Res/mm.jpg");
	layout["logo"] = new IMAGE;
	loadimage(layout["logo"], "./Res/mm.jpg");

	action["Ìø¿³"].first = 8;//´æ·ÅÍ¼Æ¬Ö¡Êý
	action["Ìø¿³"].second = new IMAGE[2];//´æ·ÅÍ¼Æ¬ÕÅÊý
	loadimage(action["Ìø¿³"].second+0, "./Res/lefty.bmp");
	loadimage(action["Ìø¿³"].second+1, "./Res/left.bmp");

}
