#include"Res.h"

int main() {
	initgraph(800, 600);

	Res::ShowLayout(0, 0, "±³¾°");
	BeginBatchDraw();
	int frame = 0;
	while (true)
	{
		cleardevice();
		Res::ShowLayout(0, 0, "±³¾°");
		
		Res::ShowAction(100, 100, "Ìø¿³", frame++);
		FlushBatchDraw();
		if (frame >= 8) {
			frame = 0;
		}
		Sleep(100);
	}

	closegraph();
	return 0;
}
