#include<iostream>
#include"../global.h"
using namespace std;
void Make_move(mov& mv)
{
	short to=mv.to;
	short from=mv.from;
	short capture=mv.capture;
	piece[board[from]]=to;
	piece[capture]=0;
	board[to]=board[from];
	board[from]=0;
	side=1-side;
}
void Un_move(mov& mv)
{
	short to=mv.to;
	short from=mv.from;
	short capture=mv.capture;
	board[from]=board[to];
	board[to]=capture;
	piece[capture]=to;
	piece[board[from]]=from;
	side=1-side;
}

