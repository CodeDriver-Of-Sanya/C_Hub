#include<stdio.h>

int getMin(int a, int b) {
	return(a < b ? a : b);
}

int getMinPath(int map[5][5]) {
	//用于存储走过时的路径值
	int dp[5][5] = { 0 };

	for (int i = 1; i < 5; i++)//往下
	{
		for (int j = 1; j < 5; j++) {//往右
			if (1 == i) {//只考虑有从左边来的可能
				dp[i][j] = dp[i][j - 1] + map[i][j];
			}
			else if (1 == j) {//只考虑有从上边来的可能
				dp[i][j] = dp[i - 1][j] + map[i][j];
			}
			else {//可能从左边来，也可能从上边来
				dp[i][j] = getMin(dp[i][j - 1], dp[i - 1][j]) + map[i][j];
			}
		}
	}
	return dp[4][4];
}

int main() {
	int map[5][5] = {
		{ 0, 0, 0, 0, 0 },
		{ 0, 3, 6, 2, 1 },
		{ 0, 4, 3, 0, 6 },
		{ 0, 5, 5, 4, 3 },
		{ 0, 9, 7, 2, 8 }
	};

	printf("最短路径和:%d\n",getMinPath(map));

	while (1);
	return 0;
}
