#include<stdio.h>

/*
背包容量：20

物品：	A		B		C		D		E
体积：	3		5		6		7		9
价值：	2		8		7		4		1

*/
//背包容量
#define V 20
//物品种类
#define N 5

struct WuPin {
	int w;//体积
	int c;//价值
};

struct WuPin wp[N] = {
	{ 3, 2 }, { 5, 8 }, { 6, 7 }, { 7, 4 }, {9,1}
};

int Max(int a, int b) {
	return ((a > b) ? a : b);
}

int main() {
	int temp[100] = { 0 };

	for (int i = 0; i < N; i++)//种类搭配
	{
		for (int j = wp[i].w ; j <= V; j++)//体积变化
		{
			//记录当前体积最大价值
			temp[j] = Max(temp[j], temp[j - wp[i].w] + wp[i].c);
			printf("i:%d j:%d temp[%d-%d]:%d,temp[%d]:%d\n",
				i, j, j, wp[i].w, temp[j - wp[i].w], j, temp[j]);
		}
	}
	printf("最大价值:%d\n", temp[V]);

	while (1);
	return 0;
}
