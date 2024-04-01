#include "berth.h"
using namespace std;

bool check_valid(const int& x, const int& y)
{
	if (x < 200 && x >= 0 && y < 200 && y >= 0 && grid[x][y] != '*' && grid[x][y] != '#')
	{
		return true;
	}
	return false;
}

bool check_valid(const MyPair& x)
{
	return check_valid(x.first, x.second);
}


Berth::Berth(int x, int y, int loading_speed) {
	this->x = x;
	this->y = y;
	this->loading_speed = loading_speed;
}
