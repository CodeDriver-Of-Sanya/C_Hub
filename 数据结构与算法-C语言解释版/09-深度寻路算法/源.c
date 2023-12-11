#include<stdio.h>
#include<stdbool.h>
#include<windows.h>
#include"res.h"
#include"myStack.h"

//加个界面
void printMap(int map[ROW][COL],myPoint* curPos) {
	system("cls");
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++) {
			if (curPos->row == i && curPos->col == j) {
				printf("人");
			}
			else {
				if (map[i][j]) {
					printf("墙");
				}
				else {
					printf("  ");
				}
			}
		}
		printf("\n");
	}
}
void printPathMap(int map[ROW][COL], myStack stack, myPoint* curPos) {
	printf("\n");
	int step = 0;
	myPoint* p = (stack.pBuff) + step;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++) {

			if (p->row < i && p->col == j) {
				i = p->row;
			}
			if (p->row == i && p->col == j) {
				map[i][j] = 2;
				step++;
				p = (stack.pBuff) + step;
			}

		}
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++) {
			if (curPos->row == i && curPos->col == j) {
				printf("囚");
			}
			else {
				if (1==map[i][j]) {
					printf("墙");
				}
				if (2 == map[i][j]) {
					printf("口");
					continue;
				}
				if (0 == map[i][j]) {
					printf("  ");
				}
			}
		}
		printf("\n");
	}
}

/*
深度寻路算法：
	寻路算法：通过算法，规划一条从起点到终点的路径
	深度寻路的限制：只能走直线，不能走斜线
	深度寻路思想：
		1.试探：当前点的上下左右四个方向分别试探
			试探方向顺序：上，右，下，左（一般情况下，要么顺时针，要么逆时针）
			并对各方向的情况进行标记，走过的路标记走过，与障碍物一样标记为不能走
		2.碰到死胡同
			每走一步都入栈，遇到死胡同就出栈，跳到新的栈顶
		3.结束
			碰到终点结束
			栈空了结束

*/

int main() {
	int map[ROW][COL]={
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	//辅助地图（标记是否走过和试探方向）
	struct pathNode pathMap[ROW][COL] = { 0 };

	//准备一个栈
	myStack stack;
	//myPoint test[] = {
	//	{1,1},
	//	{2,1},
	//	{3,1},
	//	{4,1},
	//	{5,1}
	//};
	init(&stack);
	myPoint begPos = { 1,1 };
	myPoint endPos = { 8,8 };
	//标记起点走过，并入栈
	pathMap[begPos.row][begPos.col].isFind = true;
	push(&stack, &begPos);

	//定义一个当前点
	myPoint curPos = begPos;
	//定义一个试探点
	myPoint searchPos;
	//标记是否找到终点
	bool isFindEnd = false;

	while (true)
	{
		//开始寻路
		searchPos = curPos;
		//判断当前点的试探方向
		switch (pathMap[curPos.row][curPos.col].dir)
		{
		case p_up:
			searchPos.row--;
			//当前点试探方向改变
			pathMap[curPos.row][curPos.col].dir=p_right;
			//判断试探方向能不能走
			if (wall != map[searchPos.row][searchPos.col] &&//不是障碍物
				true != pathMap[searchPos.row][searchPos.col].isFind) {//没有走过
				//能走：
				// 位置入栈
				push(&stack, &searchPos);
				// 标记走过
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// 走(当前点变化)
				curPos = searchPos;
			}
			break;
		case p_right:
			searchPos.col++;
			//当前点试探方向改变
			pathMap[curPos.row][curPos.col].dir=p_down;
			//判断试探方向能不能走
			if (wall != map[searchPos.row][searchPos.col] &&//不是障碍物
				true != pathMap[searchPos.row][searchPos.col].isFind) {//没有走过
				//能走：
				// 位置入栈
				push(&stack, &searchPos);
				// 标记走过
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// 走(当前点变化)
				curPos = searchPos;
			}
			break;
		case p_down:
			searchPos.row++;
			//当前点试探方向改变
			pathMap[curPos.row][curPos.col].dir=p_left;
			//判断试探方向能不能走
			if (wall != map[searchPos.row][searchPos.col] &&//不是障碍物
				true != pathMap[searchPos.row][searchPos.col].isFind) {//没有走过
				//能走：
				// 位置入栈
				push(&stack, &searchPos);
				// 标记走过
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// 走(当前点变化)
				curPos = searchPos;
			}
			break;
		case p_left:
			searchPos.col--;
			//当前点试探方向改变
			pathMap[curPos.row][curPos.col].dir=p_right;
			//判断试探方向能不能走
			if (wall != map[searchPos.row][searchPos.col] &&//不是障碍物
				true != pathMap[searchPos.row][searchPos.col].isFind) {//没有走过
				//能走：
				// 位置入栈
				push(&stack, &searchPos);
				// 标记走过
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// 走(当前点变化)
				curPos = searchPos;
			}
			else {
				//不能走
				//出栈
				pop(&stack);
				//跳到栈顶
				myPoint* temp = getTop(&stack);
				curPos.row = temp->row;
				curPos.col = temp->col;
			}
			
			break;
		}
		Sleep(200);
		printMap(map, &curPos);

		//判断是否找到终点
		if (endPos.col == curPos.col&&endPos.row == curPos.row) {
			isFindEnd = true;
			break;
		}

		//判断栈是否为空
		if (isEmpty(&stack))break;
	}
	//找到终点，打印栈中位置
	if (isFindEnd) {
		printf("找到终点了！\n");
		system("pause");
		printPathMap(map, stack, &curPos);
		system("pause");
		printf("path：\n");
		while (!isEmpty(&stack))
		{
			printf("(%d , %d)\n", getTop(&stack)->row, getTop(&stack)->col);
			pop(&stack);
		}
	}
	else {
		printf("找不到终点了！\n");
	}
	//测试
	//for (int i = 0; i < 5; i++)
	//{
	//	push(&stack, &test[i]);
	//}
	//while (!isEmpty(&stack))
	//{
	//	printf("(%d , %d)\n", getTop(&stack)->row, getTop(&stack)->col);
	//	pop(&stack);
	//}

	return 0;
}