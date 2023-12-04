#pragma once
#include"AI.h"
#include"Chess.h"
#include"Man.h"
class ChessGame
{
public:
	ChessGame(Man*man,AI*ai,Chess*chess);
	void play();

private:
	Man* man;
	AI* ai;
	Chess* chess;



};