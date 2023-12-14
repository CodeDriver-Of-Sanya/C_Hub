#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
int main()
{
	int move = 0;//运动变量
	system("mode con cols=45 lines=23");//在Window下可以使用 system("mode con cols=30 lines=20") 命令设置窗体大小
	//命令行控制
	int i = 0, j = 0;
	char background[20][45];
	reset_picture(i,j,background);
	display(i,j,background);
	//for (int mov = 0 ; mov < 900 ; mov++)
	//{
	//	Sleep(1000);
	//	system("cls");
	//	move_change(&i, &j, background);//运动函数
	//	
	//	display(i, j, background);
	//}

	return 0;
}