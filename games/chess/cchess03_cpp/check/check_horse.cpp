#include<iostream>
#include"../global.h"
using namespace std;
bool check_horse(){
	short my_general=(side==0 ? piece[16] : piece[32]);//己方将的位置
	short enemy_horse[2]={
		piece[5+(side==0 ?  32 :16)],
		piece[6+(side==0 ?  32 :16)]};//对方马的位置
	for(short i=0;i<2;i++){
		short pos=enemy_horse[i];
		if(pos){//如果马没有被吃掉
			for(short k=0;k<8;k++){//8个方向
				short next=pos+Horse_direction[k];
				if(next==my_general){
					if(Horse_legal[next]){
						short leg=pos+Horse_leg[k];
						if(!board[leg]){
							//flag_checkmate=1;
							return true;}}}}}}
	return false;}
//lisp indent style,just a try...
			


