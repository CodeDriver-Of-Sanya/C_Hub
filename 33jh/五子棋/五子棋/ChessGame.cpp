#include "ChessGame.h"
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
}
//开始游戏
void ChessGame::play()
{
	chess->init();
	while (1)
	{
		//先由棋手走
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
		//由ai走
		ai->go();
		{
			if (chess->checkOver())
			{
				chess->init();
				continue;
			}
		}
	}
}
