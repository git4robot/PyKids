#include<iostream>
#include<vector>
#include"../global.h"
using namespace std;
int search(short depth,int alpha,int beta)
{
	void Gen_All_Move(vector<mov>&);
	int Weight_value();
	void Make_move(mov&);
	void Un_move(mov&);
	/******************************************************/
	int value;
	vector<mov>Move_array;
	if(depth==0)
	{
		node_num++;
		return Weight_value();
	}
	Gen_All_Move(Move_array);
	if(Move_array.size()==0 )
	{
		return -Max_value;
	}
	for(short i=0;i<Move_array.size();i++)
	{
		Make_move(Move_array[i]);
		value=-search(depth-1,-beta,-alpha);
		Un_move(Move_array[i]);
		if(value>=beta)
		{
			/**
			if(depth==max_depth)
				best_move=Move_array[i];
			*/
			return beta;
		}
		if(value>alpha)
		{
			/**
			if(depth==max_depth)
				best_move=Move_array[i];
			**/
			alpha=value;
		}
	}

	return alpha;
}


