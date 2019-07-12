#include"../global.h"
using namespace std;
bool check_chariot()
{
	short my_general=piece[(side==0 ? 16 :32)];//己方将的位置
	short enemy_chariot[2]={//敌方车的位置
		piece[7+(side==0 ? 32 :16)],
		piece[8+(side==0 ? 32 :16)]
	};
	for(short i=0;i<2;i++)
	{
		short pos=enemy_chariot[i];
		if(pos)//如果敌方的车没有被吃掉
		{
			short exist=0;
			short from=(pos<my_general ? pos :my_general);
			short to=(pos<my_general ? my_general :pos);
			if(pos%16 == my_general%16)//如果在同一列
			{
				for(short j=from+16;j!=to;j+=16)
				{
					if(board[j])//如果将与车之间有其他棋子
						exist=1;
				}
				if(!exist)
					return true;
			}
			if(pos/16 == my_general/16)//如果在同一行
			{
				for(short j=from+1;j!=to;j++)
				{
					if(board[j])//如果将与车之间有其他棋子
						exist=1;
				}
				if(!exist)
					return true;
			}
		}
	}
	return false;
}
