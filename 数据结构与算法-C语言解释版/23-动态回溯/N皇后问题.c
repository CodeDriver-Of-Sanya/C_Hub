#include<stdio.h>
#include<stdbool.h>

//皇后个数
#define N 4

//记录有多少种摆放方式（可行的解法）
int cnt = 0;

void travel(int Q[N][N]) {
	printf("------------------------------------\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", Q[i][j]);
		}
		printf("\n");
	}
}

//能放返回true 否则返回false
bool isPlace(int x, int y, int Q[N][N]) {
	//八个方向 全部都是0 就可以放 否则不能放
	//这里用排除法，判断不能放的情况

	//判断斜线需要用到的
	int xx;//x轴
	int yy;//y轴

	//判断左右 横向
	for (int i = 0; i < N; i++)
	{
		if (1 == Q[x][i] && y != i) return false;
	}
	//判断上下 纵向
	for (int i = 0; i < N; i++)
	{
		if (1 == Q[i][y] && x != i) return false;
	}
	//判断左上
	for (xx = x - 1, yy = y - 1; xx >= 0 && yy >= 0; xx--, yy--) {
		if (1 == Q[xx][yy])return false;
	}
	//判断右上
	for (xx = x + 1, yy = y - 1; xx < N && yy >= 0; xx++, yy--) {
		if (1 == Q[xx][yy])return false;
	}
	//判断左下
	for (xx = x - 1, yy = y + 1; xx >= 0 && yy < N; xx--, yy++) {
		if (1 == Q[xx][yy])return false;
	}
	//判断右下
	for (xx = x + 1, yy = y + 1; xx < N && yy < N; xx++, yy++) {
		if (1 == Q[xx][yy])return false;
	}

	return true;
}

//exist=已经存在的皇后数量
void queen(int exist, int Q[N][N]) {
	//已经摆好了N个皇后，记录一次成功的摆法
	if (N == exist) {
		travel(Q);
		cnt++;
		return;
	}

	//还没摆好
	for (int i = 0; i < N; i++)//y坐标，不需要x坐标，因为皇后走米字，一行不可能放下俩
	{
		if (isPlace(exist, i, Q)) {//能放
			Q[exist][i] = 1;//放
			queen(exist+1, Q);//放下一个
			Q[exist][i] = 0;//撤销（回退）

		}
	}
}

int main() {
	//创建棋盘
	int Q[N][N] = { 0 };//0=没有放皇后	1=放皇后

	queen(0, Q);

	printf("%d皇后问题有%d种解法!\n", N, cnt);

	while (1);
	return 0;
}
