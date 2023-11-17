#pragma once
#include <stdio.h>
#include<time.h>
#include<windows.h>
#define ROW 9//游玩范围_行数
#define COL 9//游玩范围_列数
#define ROWS ROW + 2//最外侧安全范围
#define COLS COL + 2//最外侧安全范围
#define BOOM 1//随机布置雷数


void rePut_Boom(char Boom[ROWS][COLS],int rows,int cols,char set);//初始化设置，分别对应mine数组和show数组
void show_Boom_demo(char Boom[ROWS][COLS], int rows, int cols);//打印棋盘——测试
void Set_mine(char Boom[ROWS][COLS], int row, int col);//布雷函数
int Juage_MY(char mine[ROWS][COLS], int x, int y);//判断周围8个位置有多少雷
int judage_Win(char mine[ROWS][COLS],int row,int col);//判断是否胜利

/////////////////测试函数///////////////////////////////////////////////////////////////////////////////
void convinence_show(char show[ROWS][COLS],char mine[ROWS][COLS], int row, int col,int x,int y);//空地雷位置直接清屏