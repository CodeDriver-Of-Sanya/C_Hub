#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

void printMainMenu() {
	cout << "---请出拳---" << endl;
	cout << "--1.石头" << endl;
	cout << "--2.剪刀" << endl;
	cout << "--3.布" << endl;
	cout << "------------" << endl;
}

void isWin() {
	int playerSel;
	cin >> playerSel;
	srand((unsigned int)time(NULL));
	int aiSel = rand() % 3 + 1;
	if (playerSel == aiSel) {
		cout << "平手" << endl;
	}
	else if ((playerSel + 1 == aiSel) || (playerSel == 3 && aiSel == 1)) {
		cout << "你赢了！" << endl;
	}
	else {
		cout << "你输了" << endl;
	}
}


int main() {
	while (true)
	{
		printMainMenu();
		isWin();
		system("pause");
		system("cls");
	}

	return 0;
}
