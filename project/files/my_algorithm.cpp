#include "my_algorithm.h"
bool visited[200][200];
namespace my_alg {
	void init_dis()
	{
		memset(dis, -1, sizeof(dis));
		unique_ptr<unique_ptr<unique_ptr<bool[]>[]>[]> vis(new unique_ptr<unique_ptr<bool[]>[]>[200]);
		for (int i = 0; i < 200; ++i)
		{
			vis[i].reset(new std::unique_ptr<bool[]>[200]);
			for (int j = 0; j < 200; ++j)
			{
				vis[i][j].reset(new bool[berth_num]);
				for (int k = 0; k < berth_num; ++k)
				{
					vis[i][j][k] = false;
				}
			}
		}
		queue<MyPair> q;
		for (int i = 0; i < berth_num; i++)
		{
			q.push({ berth[i].x, berth[i].y });
			dis[berth[i].x][berth[i].y][i] = 0;
			vis[berth[i].x][berth[i].y][i] = true;
			while (!q.empty())
			{
				MyPair tmp = q.front();
				q.pop();
				for (int j = 0; j < 4; j++)
				{
					MyPair cur = tmp + dx_dy[j];
					if (Robot::land_check_valid(cur.first, cur.second) && !vis[cur.first][cur.second][i])
					{
						vis[cur.first][cur.second][i] = true;
						dis[cur.first][cur.second][i] = dis[tmp.first][tmp.second][i] + 1;
						q.push(cur);
					}
					else if(Boat::sea_check_valid(cur.first, cur.second) && !vis[cur.first][cur.second][i])
					{
						vis[cur.first][cur.second][i] = true;
						dis[cur.first][cur.second][i] = dis[tmp.first][tmp.second][i] + 1;
						q.push(cur);
					}
				}
			}
		}
	}
}