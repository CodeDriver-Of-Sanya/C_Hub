#include"ExWindow.h"
#include"ExLine.h"

int main(){

	ExWindow* window = new ExWindow(800, 600, "C:\\Users\\zmq\\coding\\C++\\画图小工具（easyx用c++类封装）\\bg.gif");
	ExLine* line = new ExLine;
	while (true)
	{
		ExMessage msg;
		while (peekmessage(&msg)) {
			line->draw(msg);
		}
	}
	return 0;
}
