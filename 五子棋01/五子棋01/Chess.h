#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
//表示落子位置
struct ChessPos
{
	int row;
	int val;
};

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;


class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);


	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();
	bool checkOver();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;
	int margin_x;
	int margin_y;
	float chessSize;
	vector<vector<int>>chessMap;


	bool playerFlag;
};
