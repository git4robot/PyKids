#include<iostream>
#include<vector>
#include"../global.h"
using namespace std;
void Horse_move(short pos,short Side_tag,vector<mov>& Move_array)
{
	void Save_move(short&,short&,vector<mov>&);
	for(short i=0;i<8;i++)
	{
		short leg=pos+Horse_leg[i];//Horse_leg[i]储存马脚绝对位置相对与当前position的偏移量
		short next=pos+Horse_direction[i];//Horse_direction[i]储存可走的位置相对当前position的偏移量
		if(Horse_legal[next])//如果可能的位置在棋盘上
		{
			if(!board[leg])//如果马脚位置上没有棋子
			{
				if( ! (board[next] & Side_tag))//如果要走的位置上没有本方棋子
				{
					Save_move(pos,next,Move_array);
				}
			}
		}
	}
}

