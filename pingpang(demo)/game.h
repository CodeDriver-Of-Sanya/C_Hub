#pragma once
#include <stdio.h>
#include <windows.h>
#define ROW 20
#define COL 45
void reset_picture(int i , int j , char background[ROW][COL])//初始化display数组函数
{
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if ((i == 0 && j == 0) || (i == 0 || i == 19) && (j == 44 || j == 0))
			{
				background[i][j] = '+';
			}
			else if (i == 0 || i == ROW - 1)
			{
				background[i][j] = '-';
			}
			else if (j == 0 || j == COL - 1)
			{
				background[i][j] = '|';
			}
			else
				background[i][j] = ' ';
		}
	}
}

void display(int i, int j, char background[ROW][COL])//展示图形函数
{
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			printf("%c", background[i][j]);
		}
	}
}

void move_change(int* i , int* j , char background[ROW][COL])//图形变化函数
{
	background[*i][*j] = ' ';
	if (*j < COL)
	{
		background[*i][*j + 1] = '0';
	}
	else
	{
		*j = 0;
		background[*i + 1][*j] = '0';
	}
}