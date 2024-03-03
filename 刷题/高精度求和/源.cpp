#include<iostream>
#define N 10000//定义数组容量，也可以自己改成malloc形式

using namespace std;

int main() {
	int firstNum[N] = { 0 };
	int secondNum[N] = { 0 };
	int sum[N] = { 0 };
	//1.输入两个数并从字符转换为int
	string str1, str2;
	cin >> str1;
	//字符串转换成数字放入数组（顺便逆序一下）
	for (int i = 0; i < str1.size(); i++)
	{
		//在 数字数组的有效位数最末尾处 放 字符串中的最高位
		//这样firstNum[0]对应的就是个位
		firstNum[str1.size() - 1 - i] = str1[i] - '0';
	}
	cin >> str2;
	for (int i = 0; i < str2.size(); i++)
	{
		secondNum[str2.size() - 1 - i] = str2[i] - '0';
	}

	//2.找出这两个数的最大位数是多少
	int max = str1.size() > str2.size() ? str1.size() : str2.size();

	//3.根据最大位数进行循环，对同位进行相加
	for (int i = 0; i < max; i++)
	{
		//这里要加上sum[i]是因为前一位可能会进位
		sum[i] = sum[i] + firstNum[i] + secondNum[i];
		if (9 < sum[i]) {
			//如果这一位的数字大于9，说明是10以上，要进位
			sum[i + 1] = sum[i] / 10;
			sum[i] = sum[i] % 10;
		}
	}
	//去掉最高位前面的0
	if (0 == sum[max]) {
		max--;
	}
	//从最高位开始输出和
	for (int i = max; i >= 0; i--)
	{
		cout << sum[i];
	}
	return 0;
}