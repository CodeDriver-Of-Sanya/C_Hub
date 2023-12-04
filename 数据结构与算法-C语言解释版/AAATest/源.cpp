#include<iostream>
#include<math.h>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
	string s;
	

	int cnt11W = 0;
	int cnt11L = 0;
	int cnt21W = 0;
	int cnt21L = 0;
	vector<int> vW;
	vector<int> vL;

	bool xun = true;
	while (xun) {
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'E') {
				xun = false;
				break;
			}
			switch (s[i]) {
			case 'W':
				cnt11W++;
				cnt21W++;
				break;
			case 'L':
				cnt11L++;
				cnt21L++;
				break;
			}
			if (cnt11W == 11 || cnt11L == 11) {
				std::cout << cnt11W << ":" << cnt11L << endl;
				cnt11W = 0;
				cnt11L = 0;
			}
			if (cnt21W == 21 || cnt21L == 21) {
				vW.push_back(cnt21W);
				vL.push_back(cnt21L);
				cnt21W = 0;
				cnt21L = 0;
			}
		}
	}
	cout << cnt11W << ":" << cnt11L << endl;

	cout << endl;
	for (int i = 0; i < vW.size(); i++) {
		cout << vW[i] << ":" << vL[i] << endl;
	}
	cout << cnt21W << ":" << cnt21L << endl;



	return 0;
}