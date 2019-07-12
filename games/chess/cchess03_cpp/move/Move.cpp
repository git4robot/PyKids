#include<iostream>
#include"../global.h"
#include<algorithm>
#include<vector>
using namespace std;
void Gen_All_Move(vector<mov>& Move_array)
{
	void General_move(short,short,vector<mov>&);
	void Advisor_move(short,short,vector<mov>&);
	void Elephant_move(short,short,vector<mov>&);
	void Horse_move(short,short,vector<mov>&);
	void Chariot_move(short,short,vector<mov>&);
	void Cannon_move(short,short,vector<mov>&);
	void Soldier_move(short,short,vector<mov>&);
	short Side_tag=16+side*16;//若红方,Side_tag=16;黑方,32;
	short order[16]={7,8,9,10,5,6,3,4,1,2,0,13,12,14,11,15};
	for(short i=0;i<16;i++)
	{
		short p=piece[Side_tag+i];
		if(p!=0)//说明棋子在棋盘
		{
			switch(i)
			{//这个地方可以排一下序,让好的走法出现在栈顶,可以提高剪枝的速度
				case 7:
				case 8:
					Chariot_move(p,Side_tag,Move_array);
					break;
				case 9:
				case 10:
					Cannon_move(p,Side_tag,Move_array);
					break;
				case 5:
				case 6:
					Horse_move(p,Side_tag,Move_array);
					break;
				case 0:
					General_move(p,Side_tag,Move_array);
					break;
				case 1:
				case 2:
					Advisor_move(p,Side_tag,Move_array);
					break;
				case 3:
				case 4:
					Elephant_move(p,Side_tag,Move_array);
					break;
				default:
					Soldier_move(p,Side_tag,Move_array);
			}
		}
	}

	sort(Move_array.begin(),Move_array.end(),greater<mov>());
}
void Save_move(short& from,short& to,vector<mov>& Move_array)
{
	void Make_move(mov&);
	void Un_move(mov&);
	bool checkmate();
	mov mv={from,to,board[to]};
	Make_move(mv);
	side=1-side;
	short check=checkmate();
	side=1-side;
	Un_move(mv);
	if(!check)
		Move_array.push_back(mv);

}
