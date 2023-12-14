
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define HIGH 25
void resethighBoard(char board[HIGH], int Num)//图形初始化功能
{
	int i = 0;
	for (i = 0 ; i < Num ; i++)
	{
		board[i] = '|';
	}
}
void displayhighBoard(char board[HIGH], int Num)//图形展示函数
{
	int i = 0;
	for (i = 0; i < Num; i++)
	{
		printf("%c\n",board[i]);
	}
}
int main()
{//////////////////////////////////////////////////////双缓冲区显示技术///////////////////////////
/*// 获取默认标准显示缓冲区句柄
	HANDLE hOutput;
	COORD coord = { 0, 0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	//创建新的缓冲区
	HANDLE hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	//设置新的缓冲区为活动显示缓冲
	SetConsoleActiveScreenBuffer(hOutBuf);

	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);

	//双缓冲处理显示
	DWORD bytes = 0;
	char data[3200];*/
//////////////////////////////////////////////////////////////////////////////////
	char highBoard[HIGH];
	resethighBoard(highBoard, HIGH);
	highBoard[0] = 'O';
	int i = 0;
	float start = clock();
	float middel;
	float x = 0;
	int postion;
	float size;
	int tmppostion = 0;
	while (1)
	{
		middel = clock();
		system("cls");
		x = 0.5 * 10.0 *((middel - start) / 1000)*((middel - start) / 1000);
		postion = x / 1;
		displayhighBoard(highBoard, HIGH);
		highBoard[postion] = 'O';
		if (tmppostion != postion)
		{
			highBoard[postion - 1] = '|';
		}
		if (x > 24)
		{
			break;
		}
		tmppostion = postion;
	}
////////////////////////////////////////////////////////////////////////////////////////////
	//ReadConsoleOutputCharacterA(hOutput, data, 3200, coord, &bytes);
	//WriteConsoleOutputCharacterA(hOutBuf, data, 3200, coord, &bytes);
////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}