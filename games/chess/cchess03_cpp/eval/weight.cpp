/*根据全局变量棋盘数组board[256],按照固定权重得出评价函数值*/
#include"../global.h"
#include<iostream>
using namespace std;
int Weight_value()
{
	int get_pos_value(short);
	short i=0;
	int Red_value=0,Black_value=0;
	for(i=0;i<16;i++)
	{
		short red=i+16;
		short black=i+32;
		if(piece[red])
			Red_value+=piece_weight[red]+get_pos_value(red);
		if(piece[black])
			Black_value+=piece_weight[black]+get_pos_value(black);
	}
	if(side==0)
		return (Red_value-Black_value);
	return (Black_value-Red_value);
}
int get_pos_value(short piece_num)
{
	short pos=piece[piece_num];
	switch(piece_num)
	{
		case 0:
			return 0;
		case 16:
		case 32:
			return general_pos_value[pos];
		case 17:
		case 18:
		case 33:
		case 34:
			return advisor_pos_value[pos];
		case 19:
		case 20:
		case 35:
		case 36:
			return elephant_pos_value[pos];
		case 21:
		case 22:
			return red_horse_pos_value[pos];
		case 37:
		case 38:
			return black_horse_pos_value[pos];
		case 23:
		case 24:
			return red_chariot_pos_value[pos];
		case 39:
		case 40:
			return black_chariot_pos_value[pos];
		case 25:
		case 26:
			return red_cannon_pos_value[pos];
		case 41:
		case 42:
			return black_cannon_pos_value[pos];
		case 27:case 28: case 29: case 30: case 31:
			return red_soldier_pos_value[pos];
		case 43:case 44: case 45: case 46: case 47:
			return black_soldier_pos_value[pos];
		default:
			return 0;
	}
}
