#include <iostream>

using namespace std;

enum DIR
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

struct f
{
	int xpos;
	int ypox;
	int dir;
};

int main(int argc, char** argv) {

	char map[10][10];
	for (int i = 0; i < 10; i++)
	{
		scanf("%s", map[i]);
	}


	return 0;
}