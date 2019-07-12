#include"../global.h"
#include<iostream>
using namespace std;
bool checkmate()
{
	bool check_general();
	bool check_horse();
	bool check_cannon();
	bool check_chariot();
	bool check_soldier();
	if(check_general() or check_horse() or check_cannon() or check_chariot() or check_soldier())
		return true;
	return false;
}
