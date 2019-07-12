#include<iostream>
#include"../global.h"
using namespace std;

bool check_soldier()
{
	short my_general=piece[(side==0 ? 16 : 32)];//己方将的位置
	short Side_tag=(side==0 ? 32 :16);
	short enemy_soldier[5]={
		piece[11+Side_tag],
		piece[12+Side_tag],
		piece[13+Side_tag],
		piece[14+Side_tag],
		piece[15+Side_tag]
	};//敌方兵的位置
	for(short i=0;i<5;i++)//5个棋子
	{
		short pos=enemy_soldier[i];
		if(pos)//如果在棋盘上
		{
			for(short j=0;j<3;j++)//3 directions
			{
				short next=pos+Soldier_direction[1-side][j];
				if(Soldier_legal[1-side][next])//如果是合法位置
				{
					if(next==my_general)
						return true;
				}
			}
		}
	}
	return false;
}

