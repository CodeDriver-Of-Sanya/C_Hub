#include "Man.h"

/*
开发日志
1，创建项目，导入素材
2，设计项目的框架
*/

void Man::init(Chess*chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;
	//获取鼠标点击信息
	
	//通过棋盘对象，来调用  判断落子是否有效，以及落子功能
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}
	}
	//printf("%d,%d\n", pos.col, pos.row);
	//落子
	chess->chessDown(&pos, CHESS_BLACK);

}
