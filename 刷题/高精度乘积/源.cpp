#include<iostream>
#define N 10000

using namespace std;

int main() {
	int one[N] = { 0 };
	int two[N] = { 0 };
	int product[N] = { 0 };
	string strOne, strTwo;
	cin >> strOne;
	cin >> strTwo;
	for (int i = 0; i < strOne.size(); i++)
	{
		one[i] = strOne[strOne.size() - 1 - i] - '0';
	}
	for (int i = 0; i < strTwo.size(); i++)
	{
		two[i] = strTwo[strTwo.size() - 1 - i] - '0';
	}
	//		one
	//	x	two
	//-------------
	for (int i = 0; i < strTwo.size(); i++)//two
	{
		for (int j = 0; j < strOne.size(); j++)//one
		{
			//双重循环，到后面不能保证 product[i + j] 里 没有 有效数据
			product[i + j] = product[i + j] + one[j] * two[i];
			//进位
			if (9 < product[i + j]) {
				//双重循环，到后面不能保证 product[i + j + 1] 里 没有 有效数据
				product[i + j + 1] = product[i + j + 1] + product[i + j] / 10;
				product[i + j] = product[i + j] % 10;
			}
		}
	}
	//结果的最多位数
	int length = strOne.size() + strTwo.size();
	//如果最高位上是0，那么位数--
	while (0 == product[length-1] && length > 1) {
		length--;
	}
	//从最高位开始输出
	for (int i = length-1; i >= 0; i--)
	{
		cout << product[i];
	}

	return 0;
}