#include<iostream>
#include<math.h>

using namespace std;

bool weishu(long long int n) {
	if ((1000 <= n && n <= 9999) || (100000 <= n && n <= 999999) || (10000000 <= n && n <= 99999999) || (100000000 == n))return false;
	return true;
}

bool huiwen(long long int n) {
	long long int un = 0;
	long long int temp = n;
	//先判断个位是不是0.要是0的话直接就返回false，因为只有0会是自身的回文
	if (0 == n % 10) {
		return false;
	}
	while (temp) {
		un = un * 10 + (temp % 10);
		temp /= 10;
	}
	if (n == un) {
		return true;
	}
	else {
		return false;
	}
}

bool zhishu(long long int n) {
	for (long long int i = 2; i <= sqrt(n); i++) {
		if (0 == n % i) {
			return false;
		}
	}

	return true;
}

int main() {
	long long int a, b;
	cin >> a >> b;
	//进行奇数循环，因为偶数肯定不是质数
	if (0 == a % 2) {
		a++;
	}
	for (long long int i = a; i <= b; i += 2)
	{
		if (weishu(i)) {
			if (huiwen(i)) {
				if (zhishu(i)) {
					cout << i << endl;
				}
			}
		}
	}
	return 0;
}