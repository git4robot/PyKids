#include<stdio.h>
#include<iostream>
#include<string>
#include"global.h"
using namespace std;
string get_piece(short& piece_num)
{
	switch(piece_num)
	{
		case 16:return "r_g";
		case 17:
		case 18:return "r_a";
		case 19:
		case 20:return "r_e";
		case 21:
		case 22:return "r_h";
		case 23:
		case 24:return "r_ch";
		case 25:
		case 26:return "r_ca";
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:return "r_s";
		case 32:return "b_g";
	    case 33:
		case 34:return "b_a";
		case 35:
		case 36:return "b_e";
		case 37:
		case 38:return "b_h";
		case 39:
		case 40:return "b_ch";
		case 41:
		case 42:return "b_ca";
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:return "b_s";
		default:return "0   ";
	}
}
void display()
{
	short p;
	for(int i=3;i<13;i++)
	{
		for(int j=3;j<12;j++)
		{
			p=board[i*16+j];
			cout<<'('<<i*16+j<<','<<get_piece(p)<<','<<p<<')'<<"\t";
		}
		cout<<"\n\n"<<endl;
	}
}
