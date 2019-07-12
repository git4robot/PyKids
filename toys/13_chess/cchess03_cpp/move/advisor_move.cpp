#include<iostream>
#include<vector>
#include"../global.h"
using namespace std;
void Advisor_move(short pos,short Side_tag,vector<mov>& Move_array)
{
	void Save_move(short&,short&,vector<mov>&);
	short i=0;
	for(i=0;i<4;i++)
	{
		short next=pos+Advisor_direction[i];
		if(Advisor_legal[next])//如果该位置是合法的
		{
			if(!(board[next] & Side_tag))
			{
				Save_move(pos,next,Move_array);
			}
		}
	}
}
//仕的代码跟将差不多,复制过来把General替换成Advisor即可
