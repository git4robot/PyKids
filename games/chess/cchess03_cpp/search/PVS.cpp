#include<iostream>
#include<vector>
#include"../global.h"
using namespace std;
int PVS(short depth,int alpha,int beta)
{
	void Gen_All_Move(vector<mov>&);
	int Weight_value();
	void Make_move(mov&);
	void Un_move(mov&);
	int search(short,int,int);


	int value;
	vector<mov>Move_array;
	bool pv_flag=false;


	if(depth==0)
	{
//		node_num++;
		return Weight_value();
	}


	Gen_All_Move(Move_array);
	if(Move_array.size()==0)//may not be nessary
	{
		return -Max_value;
	}


	for(short i=0;i<Move_array.size();i++)
	{
		cout<<i<<"/"<<Move_array.size()<<endl;//to gao nan: you may do something here....
//		cout<<"i="<<i<<","<<"flag:"<<pv_flag<<endl;
		mov mv=Move_array[i];
		Make_move(mv);
		if(pv_flag)
		{
			value=-search(depth-1,-alpha-1,-alpha);
			if(value>alpha && value<beta)
			{
//				cout<<"fuck_i="<<i<<endl;
//				cout<<'\t'<<mv.from<<","<<mv.to<<endl;
				value=-search(depth-1,-beta,-alpha);//CAUTION
			}
			else
			{
//				cout<<"success_i="<<i<<endl;
			}
		}
		else
		{
			value=-search(depth-1,-beta,-alpha);//caution!
		}
		Un_move(mv);
//		cout<<"value="<<value<<endl;
//		cout<<"beta="<<beta<<endl;
		if(value>=beta)
		{
//			cout<<"value="<<value;
//			cout<<"beta="<<beta;
			if(beta==Max_value)
			{
				cout<<"i="<<i<<endl;
				best_move=mv;
			}
			return value;//is it OK?
		}
		if(value>alpha)
		{
			alpha=value;
			pv_flag=true;
			if(depth==max_depth)
				best_move=mv;
		}
	}
	return value;
}


	

