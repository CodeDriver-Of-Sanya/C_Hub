#include<stdio.h>
#include<malloc.h>
#include<string.h>

int main() {
	int N;
	printf("请输入字符串长度：");
	scanf("%d", &N);
	int* pBuff = malloc(sizeof(int) * N);
	printf("请输入字符串（用空格隔开）：");
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &pBuff[i]);
	}
	//创建一个临时数组
	int* pMaxLen = malloc(sizeof(int) * N);
	memset(pMaxLen, 0, sizeof(int) * N);

	int maxPos = 1;//下标
	int nTemp;
	for (int i = 2; i < N; i++)//从第三个开始到串的末尾
	{
		//实时记录当前最大上升串长度
		nTemp = 1;
		for (int j = 1; j < i; j++)//从pBuff[i]前面的串里找最大上升串
		{
			//找比当前数据小的数据
			if (pBuff[j] < pBuff[i]) {
				if (nTemp < pMaxLen[j]) {
					nTemp = pMaxLen[j];
				}
			}
			pMaxLen[i] = nTemp + 1;
			printf("i:%d,j:%d pMaxLen[%d]:%d\n", i, j, i, pMaxLen[i]);
		}
	}

	printf("最大上升子串的长度为：%d\n", pMaxLen[N - 1]);

	while (1);
	return 0;
}
