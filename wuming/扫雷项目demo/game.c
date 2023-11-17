#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "game.h"

void rePut_Boom(char Boom[ROWS][COLS], int rows, int cols, char set)//针对性初始化函数
{
	int i = 0, j = 0;
	for (i = 0; i < 11; i++)
	{
		for (j = 0 ; j < 11 ; j++)
		{
			if (set == '0')
			{
				Boom[i][j] = '0';
			}
			else
			Boom[i][j] = '*';
		}
	}
	
}

void show_Boom_demo(char Boom[ROWS][COLS],int rows,int cols)//打印棋盘函数display
{
	int i = 0, j = 0;
	for (i = 0; i <= ROW; i++)
	{
		printf("%d ",i);
	}
	printf("\n");
	for (i = 1 ; i <= ROW ; i++)
	{
		printf("%d ",i);
		for (j = 1 ; j <= COL; j++)
		{
			printf("%c ",Boom[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------------------------\n");

}

void Set_mine(char Boom[ROWS][COLS], int row, int col)//进行布雷操作函数
{
	int x = 0, y = 0;
	
	int count = BOOM;
	while (count)
	{
		x = rand() % row + 1;
		y = rand() % col + 1;
		if (Boom[x][y] == '0')
		{
			Boom[x][y] = '1';
			count--;
		}
	}
}
////////////////////////////////判断周围雷数函数/////////////////////////////////////////////////
int Juage_MY(char mine[ROWS][COLS], int x, int y)//判断周围位置雷的个数/
{
	int Num = mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] - 8 * '0';
	return Num;
}
/////////////////////////////////////////////////////////////////////////////////////

int judage_Win(char show[ROWS][COLS], int row, int col)//判断是否胜利
{
	int count = 0;
	int i = 0, j = 0;
	for (i = 1 ; i < row + 1 ; i++)
	{
		for (j = 1 ; j < col + 1 ; j++)
		{
			if (show[i][j] != '*')
			{
				count++;
			}
		}
	}
	return count;
	
}
/////////////////////////////测试阶段////////////////////////////////////
/*/////////////////////利用递归进行爆炸清屏操作////////////////////////////

void convinence_show(char show[ROWS][COLS], char mine[ROWS][COLS], int row, int col,int x,int y)//空地雷位置直接清屏
{
	int todo = 0;
	todo = Juage_MY(mine, x - 1, y -1);
	if (todo == 0)
	{
		show[x - 1][y - 1] = '0';
		convinence_show(show, mine, ROW, COL, x - 1, y - 1);
	}
}

*/////////////////////////////测试阶段////////////////////////////////////
