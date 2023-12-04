#include<iostream>
#include"ChessGame.h"



int main()
{
	Man man;
	Chess chess(15, 52, 25, 53.9);
	AI ai;
	ChessGame game(&man,&ai,&chess);

	game.play();


	return 0;

}