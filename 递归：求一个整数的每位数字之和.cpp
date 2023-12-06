#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int DigitSum(int Num)//分离每位数字并求和
{
	int tmp = 0, acs = 0;
	if (Num > 9)
	{
		return DigitSum(Num / 10) + Num %10;//每次的返回值都包含着内部其余的数字和当前本层函数所分离的个位
		
	}
	return Num;

	
}
/*
其余写法：
int DigitSum(int Num)
{
	int tmp = Num % 10;
	if (Num > 9)
	{
		tmp = DigitSum(Num / 10) + tmp;
	}

	return tmp;
}
*/
int main()
{
	int Num = 0;
	scanf("%d", &Num);
	printf("%d",DigitSum(Num));
	return 0;
}