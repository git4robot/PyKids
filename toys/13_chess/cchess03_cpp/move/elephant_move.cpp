#include<iostream>
#include<vector>
#include"../global.h"
using namespace std;
void Elephant_move(short pos,short Side_tag,vector<mov>& Move_array)
{
	void Save_move(short&,short&,vector<mov>&);
	for(short i=0;i<4;i++)
	{
		short eye=pos+Elephant_eye[i];
		short next=pos+Elephant_direction[i];
		if(Elephant_legal[next] && (! board[eye]) && (! (board[next] & Side_tag)))
		{
			Save_move(pos,next,Move_array);
		}
	}
}
//与horse_move的代码基本一致

