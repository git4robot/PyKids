#include"../global.h"
#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
void Cannon_move(short pos,short Side_tag,vector<mov>& Move_array)
{
	void display();
	void Save_move(short&,short&,vector<mov>&);
	for(short i=0;i<4;i++)
	{
		short overflag=0;//表示未翻山
		for(short j=1;j<10;j++)
		{
			short next=pos + j*Cannon_direction[i];
			if(! Cannon_legal[next])//若不在棋盘上,此方向循环结束
				break;
			if(! board[next])//若棋盘上无子,检查翻山标志
			{
				if(! overflag)//若未翻山,则生成走法,否则不处理
				{
					/**************************************************************for debugging
					if(Side_tag==16 && pos==0x5a && next==0xca)
					{
						cout<<"board[pos]:"<<board[pos]<<endl;
						cout<<"board[next]:"<<board[next]<<endl;
						display();
						for(short k=0;k<3;k++)
						{
							for(short m=0;m<16;m++)
								printf("(%d,%x)\t",k*16+m,piece[k*16+m]);
							printf("\n");
						}
					}
					********************************************************************/
					Save_move(pos,next,Move_array);
				}
			}
			else if(!overflag)//若棋盘有子,且未翻山,则做翻山标志
				overflag=1;
			else if(! (board[next] & Side_tag))//若有子,已翻山,对方棋子
			{
				Save_move(pos,next,Move_array);
				break;
			}
			else
				break;
		}
	}
}


