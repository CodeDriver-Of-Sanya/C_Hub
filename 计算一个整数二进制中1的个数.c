#define _CRT_SECURE_NO_WARNINGS 1//计算一个整数二进制中1的个数
#include <stdio.h>
int main()
{
	int i = 0;
	int a = 7;
	int tmp = 0;
	int Num = 0;//创建四个需要用到的变量
	for (i = 0 ; i < 32 ; i++)//循环32次
	
	{
		tmp = a & 1;//判断a的最后一位是否为1
		a >>= 1;
		Num = tmp + Num;//如果为1，Num加1
	}
	printf("%d",Num);//输出Num
	return 0;
}