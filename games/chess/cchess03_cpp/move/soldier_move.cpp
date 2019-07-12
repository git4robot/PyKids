#include"../global.h"
#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;
void Soldier_move(short pos,short Side_tag,vector<mov>& Move_array)
{
	void Save_move(short&,short&,vector<mov>&);
	short i=0;
	for(i=0;i<3;i++)
	{
		short next=pos+Soldier_direction[side][i];
		if(Soldier_legal[side][next])//如果位置合法,卒的合法位置对红黑双方是有区别的
		{
			if(!(board[next] & Side_tag))
			{
				Save_move(pos,next,Move_array);
			}
		}
	}
}

