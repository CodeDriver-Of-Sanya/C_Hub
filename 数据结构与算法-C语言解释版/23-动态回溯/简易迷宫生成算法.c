#include <stdio.h>
int size;
//迷宫
int** migong = NULL;

//创建迷宫
void createMap();

//显示迷宫
void showMap();

int main() {
	createMap();
	showMap();


	while (1);
	return 0;
}

//创建迷宫
void createMap() {
	//0 用户输入大小
	printf("请输入迷宫宽高:");
	scanf("%d", &size);
	//1 开内存
	migong = malloc(sizeof(int*) * (size + 2));
	for (int i = 0; i < (size + 2); i++) {
		migong[i] = malloc(sizeof(int) * (size + 2));
		memset(migong[i], 0, sizeof(int) * (size + 2));
	}

	//2 边框设置为1
	for (int i = 0; i < (size + 2); i++) {
		migong[0][i] = migong[size + 1][i] = 1;
		migong[i][0] = migong[i][size + 1] = 1;
	}
	//3 内部
	for (int i = 1; i < size + 1; i++) {
		for (int j = 1; j < size + 1; j++) {
			switch (rand() % 10) {
			case 0:
			case 1:
				migong[i][j] = 1;
				break;
			}
		}
	}
}

//显示迷宫
void showMap() {
	for (int i = 0; i < size + 2; i++) {
		for (int j = 0; j < size + 2; j++) {
			printf("%d ", migong[i][j]);
		}
		printf("\n");
	}
}