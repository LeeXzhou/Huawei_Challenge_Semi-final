#include "my_algorithm.h"
bool visited[200][200];
namespace my_alg {
	void init_dis()
	{
		memset(land_dis, -1, sizeof(land_dis));
		memset(delivery_dis, 0x3f, sizeof(delivery_dis));
		memset(berth_dis, 0x3f, sizeof(berth_dis));
		bool vis[200][200][10] = { false };
		/*unique_ptr<unique_ptr<unique_ptr<bool[]>[]>[]> vis(new unique_ptr<unique_ptr<bool[]>[]>[200]);
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
		}*/
		queue<MyPair> q;
		for (int i = 0; i < berth_num; i++)
		{
			q.push({ berth[i].x, berth[i].y });
			land_dis[berth[i].x][berth[i].y][i] = 0;
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
						land_dis[cur.first][cur.second][i] = land_dis[tmp.first][tmp.second][i] + 1;
						q.push(cur);
					}
				}
			}
		}
		queue<Foursome>qq;
		MyTuple tuple_tmp;
		for (int k = 0; k < berth_num + delivery_num; k++) {
			int i = (k >= berth_num ? k - berth_num : k);
			memset(vis, false, sizeof(vis));
			if (k >= berth_num) {

				for (int j = 0; j < 4; j++)
				{
					Foursome tmp = Foursome(delivery_point[i].first, delivery_point[i].second, j, 0);
					tuple_tmp = tmp.get_tuple();
					if (Boat::check_valid(tuple_tmp))
					{
						//if(!vis[tuple_tmp.x][tuple_tmp.y][tuple_tmp.status])
						qq.push(tmp);
					}
				}

				delivery_dis[delivery_point[i].first][delivery_point[i].second][i] = 0;
				vis[delivery_point[i].first][delivery_point[i].second][i] = true;
				while (!qq.empty())
				{
					Foursome u = qq.front();
					qq.pop();
					for (int j = 0; j <= 2; j++)
					{
						Foursome tmp = u;
						tuple_tmp = u.get_tuple();
						if (Boat::operate(tuple_tmp, j))
						{
							if (!vis[tuple_tmp.x][tuple_tmp.y][tuple_tmp.status])
							{
								vis[tuple_tmp.x][tuple_tmp.y][tuple_tmp.status] = true;
								Foursome foursome_tmp;
								delivery_dis[tuple_tmp.x][tuple_tmp.y][i] = min(
									delivery_dis[tuple_tmp.x][tuple_tmp.y][i], u.flag +
									Boat::slow_or_not(tuple_tmp) + 1
								);
								foursome_tmp = Foursome(tuple_tmp.x, tuple_tmp.y, tuple_tmp.status, u.flag + Boat::slow_or_not(tuple_tmp) + 1);
								qq.push(foursome_tmp);
							}
						}

					}
				}
			}
			else {
				for (int j = 0; j < 4; j++)
				{
					Foursome tmp = Foursome(berth[i].x, berth[i].y, j, 0);
					tuple_tmp = tmp.get_tuple();
					if (Boat::check_valid(tuple_tmp))
					{
						//if(!vis[tuple_tmp.x][tuple_tmp.y][tuple_tmp.status])
						qq.push(tmp);
					}
				}

				berth_dis[berth[i].x][berth[i].y][i] = 0;
				vis[berth[i].x][berth[i].y][i] = true;
				while (!qq.empty())
				{
					Foursome u = qq.front();
					qq.pop();
					for (int j = 0; j <= 2; j++)
					{
						Foursome tmp = u;
						tuple_tmp = u.get_tuple();
						if (Boat::operate(tuple_tmp, j))
						{
							if (!vis[tuple_tmp.x][tuple_tmp.y][tuple_tmp.status])
							{
								vis[tuple_tmp.x][tuple_tmp.y][tuple_tmp.status] = true;
								Foursome foursome_tmp;
								berth_dis[tuple_tmp.x][tuple_tmp.y][i] = min(
									berth_dis[tuple_tmp.x][tuple_tmp.y][i], u.flag +
									Boat::slow_or_not(tuple_tmp) + 1
								);
								foursome_tmp = Foursome(tuple_tmp.x, tuple_tmp.y, tuple_tmp.status, u.flag + Boat::slow_or_not(tuple_tmp) + 1);
								qq.push(foursome_tmp);
							}
						}

					}
				}
			}
		}
	}
	void all_boat_control()
	{
		for (int i = 0; i < boat_num; i++)
		{
			boat[i].Boat_control();
		}
	}
	void all_robot_control()
	{
		for (int i = 0; i < robot_num; i++)
		{
			robot[i].robot_control();
		}
	}
	void get_left_num()
	{
		for (int i = 0; i < berth_num; i++)
		{
			berth[i].left_num = berth[i].num;
		}
		//cerr << boat_num << endl;
		for (int i = 0; i < boat_num; i++)
		{
			if (boat[i].aim_berth != -1)
			{
				berth[boat[i].aim_berth].left_num = max(0, berth[boat[i].aim_berth].left_num - boat_capacity + boat[i].goods_num);
			}
		}
	}
	void test_robot()
	{
		boat_option.clear();
		robot_option.clear();
		if (money >= 2000 && robot_num < robot_num_max)
		{
			cout << "lbot " << robot_purchase_point[robot_num % robot_purchase_point.size()].first << " " << robot_purchase_point[robot_num % robot_purchase_point.size()].second << endl;
			start_record[robot_num + 1] = { frame_id, all_num };
		}

		get_left_num();

		thread t1(all_boat_control), t2(all_robot_control);
		t1.join(); t2.join();
		for (int i = 0; i < boat_option.size(); i++)
		{
			cout << boat_option[i] << endl;
		}
		for (int i = 0; i < robot_option.size(); i++)
		{
			cout << robot_option[i] << endl;
		}
	}
}