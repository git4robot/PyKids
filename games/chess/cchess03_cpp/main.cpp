#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include"global.h"
using namespace std;
int main()
{
	int Weight_value();
	void Gen_All_Move(vector<mov>&);
	short search(short,int,int);
	int PVS(short,int,int);
	string get_piece(short&);
	void display();
	void Make_move(mov&);
	void Un_move(mov&);
	/**********************************************************/
	side=1;//black first;
	mov red,black;
	vector<mov>human_move;
	int value;
    /*************************for test***********************
	piece[45]=0;
	board[0x67]=0;

	board[0x67]=26;
	piece[26]=0x67;
	board[0xaa]=0;

	board[0x77]=25;
	piece[25]=0x77;
	board[0xa4]=0;
	***/



	/*************
	board[0x97]=0;
	piece[29]=0;

	board[0x97]=42;//black cannon;
	piece[42]=0x97;
	board[0x4a]=0;

	board[0x78]=41;
	piece[41]=0x78;
	board[0x54]=0;
	****************/
//	max_depth=2;
	cout<<"input search depth:"<<endl;
	cin>>max_depth;
	short i=0;
	vector<int>black_v;
	while(1)// no general killed
	{
		node_num=0;
//		max_depth=(i<25 ? 6 :7);
		cout<<"max_depth:"<<max_depth<<endl;
		cout<<"回合:"<<i<<endl;
//		if(i<10)
			i++;
		value=PVS(max_depth,-Max_value,Max_value);	
		cout<<"depth:"<<max_depth<<", node_num:"<<node_num<<endl;
		black_v.push_back(value);
		for(short j=0;j<black_v.size();j++)
			cout<<"black_v:"<<black_v[j]<<'\t';
		cout<<'\n'<<endl;
		/*******************/
		/***************************/
		if(value==-Max_value)//here changed!
		{
			cout<<"AI lose!"<<endl;
			break;
		}
		Make_move(best_move);//black move
		cout<<"move_piece: "<<get_piece(board[best_move.to])<<endl;
		printf("black_move:%d,%d\n",best_move.from,best_move.to);
		cout<<"capture: "<<get_piece(best_move.capture)<<endl;
		cout<<"black_value: "<<value<<endl;
		display();
		cout<<"======================================================================================================="<<endl;
		human_move.clear();
		Gen_All_Move(human_move);
		cout<<"side:"<<side<<endl;
		cout<<"human_move_size:"<<human_move.size()<<endl;
		if(human_move.size()<=10)
		{
			cout<<"you might have been checked"<<endl;
			for(short k=0;k<human_move.size();k++)
			{
				cout<<human_move[k].from<<","<<human_move[k].to<<endl;
			}
		}

		/*
		for(short i=0;i<human_move.size();i++)
			cout<<human_move[i].from<<","<<human_move[i].to<<endl;
			*/
		if(human_move.size()==0)
		{
			cout<<"human lose!"<<endl;
			break;
		}
		while(1)
		{
			cout<<"from:"<<endl;
			cin>>red.from;
			cout<<"to"<<endl;
			cin>>red.to;
			red.capture=board[red.to];
			short legal=0;
			for(short i=0;i<human_move.size();i++)
			{
				mov mv=human_move[i];
				if(red.from==mv.from && red.to==mv.to)
					legal=1;
			}
			if(legal)
			{
				Make_move(red);
				side=1-side;
				cout<<"side: "<<side<<", Weight_value: "<<Weight_value()<<endl;
				side=1-side;
				display();
				getchar();
				getchar();
				break;
			}
			else
				cout<<"illegal!\n=====================\n"<<endl;
		}
		cout<<"======================================================================================================="<<endl;
	}
}

