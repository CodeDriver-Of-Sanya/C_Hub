#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//表示落子位置
struct ChessPos
{
	int row;
	int col;
};

typedef enum
{
	CHESS_WHITE=-1,//白子
	CHESS_BLACK=1//黑子
}chess_kind_t;

class Chess
{

public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//棋盘的初始化：加载棋盘的图片，初始化棋盘的相关数据
	void init();
	//判断在指定坐标(x,y)位置，是否是有效点击
	//如果判断是有效点击，把有效点击的位置保存在参数pos中
	bool clickBoard(int x,int y,ChessPos*pos);
	//在棋盘的指定位置(pos)，落子(kind)
	void chessDown(ChessPos *pos, chess_kind_t kind);
	//获取棋盘的大小
	int getGradeSize();//获取棋盘大小
	int getChessDate(ChessPos* pos);
	int getChessDate(int row, int col);
	bool checkOver();//检查棋局是否结束
private:
	IMAGE chessBlackImg;//黑棋
	IMAGE chessWhiteImg;//白棋

	int gradeSize;//棋盘大小
	int margin_x;//定义左侧边界
	int margin_y;//顶部边界
	float chessSize;//棋子大小（棋格大小）
	//储存当前棋局的棋子分布数据0：空白 1：黑子 2：白子
	//chessMap[3][5]表示棋盘的第三行第五列的落子情况
	vector<vector<int>>chessMap;

	//表示现在该谁落子
	bool playerFlag;//ture:黑走 false：白走



};