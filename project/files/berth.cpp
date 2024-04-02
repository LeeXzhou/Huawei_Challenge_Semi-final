#include "berth.h"
using namespace std;


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