#include"../global.h"
#include<vector>
using namespace std;
void Chariot_move(short pos,short Side_tag,vector<mov>& Move_array)
{
	void Save_move(short&,short&,vector<mov>&);
	for(short i=0;i<4;i++)
	{
		for(short j=1;j<10;j++)
		{
			short next=pos+j*Chariot_direction[i];
			if(! Chariot_legal[next])
				break;

			if(! board[next])
				Save_move(pos,next,Move_array);
            else
            {
				Save_move(pos,next,Move_array);
                break;
            }
            /*
			if(! board[next])
				Save_move(pos,next,Move_array);
			else if(board[next] & Side_tag)
				break;
			else
			{
				Save_move(pos,next,Move_array);
				break;
			}
            */
		}
	}
}

