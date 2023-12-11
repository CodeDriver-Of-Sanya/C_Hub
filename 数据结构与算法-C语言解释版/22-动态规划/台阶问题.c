#include<stdio.h>

#if 0
//递归方式
int taijie(int n) {
	if (n < 1)return 0;
	if (1 == n || 2 == n)return n+1;

	return taijie(n - 1) + taijie(n - 2);
}
#else
//循环方式
int taijie(int n) {
	if (n < 1)return 0;
	if (1 == n || 2 == n)return n + 1;

	//累计数
	int accumulate;
	int num1 = 2, num2 = 3;
	for (int i = 3; i <= n; i++)
	{
		accumulate = num1 + num2;
		num1 = num2;
		num2 = accumulate;
	}
	return accumulate;
}
#endif

int main() {
	int n;
	while (1)
	{
		printf("请输入要走的台阶数量：");
		scanf("%d", &n);

		printf("%d级台阶有%d种走法!\n", n,taijie(n));
	}

	return 0;
}