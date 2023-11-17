#define _CRT_SECURE_NO_WARNINGS 1//扫雷游戏
#include "game.h"
void game()//实现扫雷的游戏代码部分
{
	system("cls");
	int cols = 0, rows = 0, row = 0, col = 0;
	char mine[ROWS][COLS] = {0};
	char show[ROWS][COLS] = {0};
	//初始化藏雷数组和展示数组show
	rePut_Boom(mine, ROWS, COLS,'0');
	rePut_Boom(show, ROWS, COLS,'*');
	//布雷函数
	Set_mine(mine,ROW,COL);
	//show_Boom_demo(mine, ROWS, COLS);//测试
	//打印棋盘
	show_Boom_demo(show, ROWS, COLS);
	int x = 0, y = 0;
	printf("请输入排雷坐标：");
	while (1)
	{
		scanf("%d%d",&x,&y);
		if (x >= 1 && x <= ROW + 1 && y >= 1 && y <= COL + 1)
		{
			if (mine[x][y] == '1')
			{
				printf("排雷失败\n");
				show_Boom_demo(mine, ROWS, COLS);//打印棋盘
				break;
			}
			else
			{
				int todo = 0;
				todo = Juage_MY(mine, x, y);
				
////////测试阶段//////convinence_show(show, mine, ROW, COL,x,y);//空地雷位置直接清屏
				show[x][y] = '0' + todo;
				show_Boom_demo(show, ROWS, COLS);
				if (judage_Win(show,ROW,COL) == ROW*COL - BOOM)
				{

					printf("成功排雷\n");
					break;
				}
				printf("请输入排雷坐标：");
			}
		}
		else
		{
			printf("输入错误请重新输入：");
			continue;
		}
	}
	
}	
void menu()//菜单页面
{
	printf("*****************************************\n");
	printf("***************扫雷游戏******************\n");
	printf("*****************************************\n");
	printf("*********  1.play   0.exit  *************\n");
	printf("*****************************************\n");

}
int main()
{
	srand((unsigned int ) time(NULL));
	int inPut = 0;
	do 
	{
		menu();
		printf("请输入选项:");
		scanf("%d",&inPut);
		switch (inPut)
		{
		case 1:
			game();//进入游戏主函数
			break;
		case 0:
			break;
		default :
			printf("输入错误请重新输入：");
			continue;
		}
	} while (inPut);
	return 0;
}