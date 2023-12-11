#pragma once
#include<stdbool.h>
#define ROW 10
#define COL 10

//道路情况
enum state{road,wall,};

//试探方向
enum dir{p_up,p_right,p_down,p_left};

//试探节点类型
struct pathNode {
	//当前点的当前试探方向
	int dir;
	//是否走过
	bool isFind;
};

//点类型
typedef struct myPoint {
	int row, col;
}myPoint;
