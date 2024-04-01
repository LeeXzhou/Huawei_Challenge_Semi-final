#include "berth.h"
using namespace std;

bool land_check_valid(const int& x, const int& y)
{
	if (x < 200 && x >= 0 && y < 200 && y >= 0)
	{
		if (grid[x][y] == '.' || grid[x][y] == '>' || grid[x][y] == 'R' || grid[x][y] == 'B' || grid[x][y] == 'C' || grid[x][y] == 'c')
		{
			return true;
		}		
	}
	return false;
}

bool land_check_valid(const MyPair& x)
{
	return land_check_valid(x.first, x.second);
}


Berth::Berth(int x, int y, int loading_speed) {
	this->x = x;
	this->y = y;
	this->loading_speed = loading_speed;
}

MyPair Berth::find_goods_from_berth()
{
	priority_queue<Plan> q;
	for (auto cur = goods_info.begin(); cur != goods_info.end();)
	{
		if (cur->status <= frame_id)
		{
			cur = goods_info.erase(cur);
		}
		else
		{
			if (goods_map[cur->x][cur->y].first > 0)
			{
				//需要优化
				q.push(Plan(goods_map[cur->x][cur->y].first, dis[cur->x][cur->y][berth_id],{ cur->x,cur->y }));
			}
			cur++;
		}
	}
	if (!q.empty())
	{
		MyPair ret = q.top().target;
		return ret;
	}
	else
	{
		return make_pair(-1, -1);
	}

}