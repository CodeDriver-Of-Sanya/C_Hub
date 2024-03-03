#include<iostream>
#include<cstring>//用到了memset
#define N 100//自定义数组长度，也可自己改成malloc动态分配

using namespace std;

//阶乘用的
//multiplier 乘数
//product 乘积
int mulOne[N] = { 0 };//乘数1
int moSize = 0;//乘数1所存的数的位数
int mulTwo[N] = { 0 };//乘数2
int mtSize = 0;//乘数2所存的数的位数
int product[N] = { 0 };//乘积
int proSize = 0;//乘积所存的数的位数
//求和用的
int sum[N] = { 0 };//和
int sumSize = 0;//和所存的数的位数

//统计已经阶乘过的数，从2开始是因为1的情况可直接输出
int cnt = 2;

void jiecheng(int n) {
	//这个if和最外层的for可以优化掉
	if (n > cnt)cnt = n;//先判断已经阶乘过的数和传入的数的大小关系
	for (int i = cnt; i <= n; i++)//从没阶乘过的数开始
	{
		//将n放入mulTwo
		int temp = i;
		mtSize = 0;//每次都要重置，不然传入的不对
		while (temp)
		{
			mulTwo[mtSize++] = temp % 10;
			temp /= 10;
		}
		//开始相乘（先乘完，不管进位）
		//		one
		//	x	two
		//-------------
		for (int i = 0; i < mtSize; i++)//two
		{
			for (int j = 0; j < moSize; j++)//one
			{
				//双重循环，到后面不能保证 product[i + j] 里 没有 有效数据
				product[i + j] = product[i + j] + mulOne[j] * mulTwo[i];
			}
		}
		//处理进位
		for (int i = 0; i < mtSize + moSize; i++)
		{
			if (9 < product[i]) {
				product[i + 1] = product[i + 1] + product[i] / 10;
				product[i] = product[i] % 10;
			}
		}
		//计算乘积的位数
		int length = mtSize + moSize;
		while (0 == product[length - 1]) {
			length--;
		}
		proSize = length;
		//将此步骤算出来的product给mulOne
		for (int i = 0; i < proSize; i++)
		{
			mulOne[i] = product[i];
		}
		moSize = proSize;
		//清空product，用于下次计算存储结果
		memset(product, 0, sizeof(product));
		proSize = 0;
	}
	//最终的计算结果在mulOne中
	//for (int i = 0; i < moSize; i++)
	//{
	//	cout << mulOne[moSize - 1 - i];
	//}
	//cout << endl;
}

void qiuhe(int sum[N], int mulOne[N]) {
	//找到两个加数的最大位数
	int max = moSize > sumSize ? moSize : sumSize;
	//也是先不管进位相加
	for (int i = 0; i < max; i++)
	{
		sum[i] = sum[i] + mulOne[i];
	}
	//处理进位
	for (int i = 0; i < max; i++)
	{
		if (9 < sum[i]) {
			sum[i + 1] = sum[i + 1] + sum[i] / 10;
			sum[i] = sum[i] % 10;
		}
	}
	sumSize = max;
	if (0 == sum[sumSize - 1]) {
		sumSize--;
	}
	//for (int i = 0; i < sumSize; i++)
	//{
	//	//cout << sum[sumSize - 1 - i];
	//}
	//cout << endl;
}

int main() {
	int n;
	cin >> n;
	//对最开始的阶乘赋初值
	mulOne[0] = 1;
	moSize = 1;
	//开始计算
	for (int i = 1; i <= n; i++)
	{
		jiecheng(i);
		qiuhe(sum, mulOne);
	}
	//输出最终结果
	for (int i = 0; i < sumSize; i++)
	{
		cout << sum[sumSize - 1 - i];
	}
	return 0;
}