#include "my_algorithm.h"
bool visited[200][200];
namespace my_alg {
	void init_dis()
	{

	}
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
}