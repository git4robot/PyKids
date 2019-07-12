#include"../global.h"
bool check_cannon()
{
	short my_general=piece[(side==0 ? 16 : 32)];
	short enemy_cannon[2]={
		piece[9+(side==0 ? 32 : 16)],
		piece[10+(side==0 ? 32 : 16)]
	};
	for(short i=0;i<2;i++)
	{
		short pos=enemy_cannon[i];
		if(pos)
		{
			short from=(pos < my_general ? pos : my_general);
			short to=(pos<my_general ? my_general : pos);
			if(pos%16 == my_general%16)
			{
				short piece_num=0;
				for(short j=from+16; j!=to; j+=16)
				{
					if(board[j])
					{
						piece_num++;
					}
				}
				if(piece_num==1)
					return true;
			}
			if(pos/16 == my_general/16)
			{
				short piece_num=0;
				for(short j=from+1;j!=to;j++)
				{
					if(board[j])
					{
						piece_num++;
					}
				}
				if(piece_num==1)
					return true;
			}
		}
	}
	return false;
}
