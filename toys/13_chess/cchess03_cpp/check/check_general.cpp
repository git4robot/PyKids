#include<iostream>
#include"../global.h"
using namespace std;
bool check_general()
{
	short checkmate_flag=0;
	if(piece[16]%16 == piece[32]%16)
	{
		checkmate_flag=1;
		for(short pos=piece[16]-16;pos!=piece[32];pos-=16)
		{
			if(board[pos])
			{
				checkmate_flag=0;
				break;
			}
		}
	}
	return checkmate_flag;
}
