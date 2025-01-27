#include "berth.h"
using namespace std;

bool check_boundary(int x, int y)
{
	if (x < 0 || x >= 200 || y < 0 || y >= 200)
	{
		return false;
	}
	return true;
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
				/*int good_to_berth_dis = 300000;
				for (int i = 0; i < berth_num; i++)
				{
					if (land_dis[cur->x][cur->y][i] > 0)
					{
						good_to_berth_dis = min(good_to_berth_dis, land_dis[cur->x][cur->y][i]);
					}
				}*/
				q.push(Plan(goods_map[cur->x][cur->y].first, land_dis[cur->x][cur->y][berth_id], { cur->x,cur->y }));
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