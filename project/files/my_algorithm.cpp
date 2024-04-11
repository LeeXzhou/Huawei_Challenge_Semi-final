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

	void buy_robot()
	{
		if (no_buy)return;
		//连买多个机器人的情况，当前帧向前追溯，追溯200帧(可调)以上才可加入拉格朗日估算。
		if (money >= 2000)
		{
			if (robot_num < 11)//得至少买三次，不然日不了
			{
				if (robot_num >= 7)
				{
					predictable_num.push_back(robot_num + 1);
					edge_frames.push_back(frame_id);
				}
				
				cout << "lbot " << robot_purchase_point[robot_num % robot_purchase_point.size()].first << " " << robot_purchase_point[robot_num % robot_purchase_point.size()].second << endl;
				return;
			}
			vector<double>robot_num_tmp;
			vector<double>robot_efficiency_tmp;
			for (int i = 0; i < edge_frames.size(); i++)
			{
				if (frame_id - edge_frames[i] <= 200)break;
				double tmp;
				if (i == edge_frames.size() - 1)
				{
					tmp = 1.0 * (total_accumulate_value[frame_id-1] - total_accumulate_value[int(edge_frames[i])]) / (frame_id-1 - edge_frames[i]);
				}
				else
				{
					tmp = 1.0 * (total_accumulate_value[int(edge_frames[i+1])] - total_accumulate_value[int(edge_frames[i])]) / (edge_frames[i+1] - edge_frames[i]);
				}
				robot_num_tmp.push_back(predictable_num[i]);
				robot_efficiency_tmp.push_back(tmp);
				cerr <<"AAAA"<<edge_frames[i]<<' ' << predictable_num[i] << ' ' << tmp <<' '<<money<< endl;
			}
			vector<double>num_tmp;
			num_tmp.push_back(robot_num + 1);
			vector<double>ans = lagrange(robot_num_tmp, robot_efficiency_tmp, num_tmp);
			cerr << robot_num << ' ' << ans[0] << endl;
			if (1.0 * (ans[0] - robot_efficiency_tmp[robot_efficiency_tmp.size() - 1]) * (15000 - frame_id) > 2000)
			{
				predictable_num.push_back(robot_num+1);
				edge_frames.push_back(frame_id);
				cout << "lbot " << robot_purchase_point[robot_num % robot_purchase_point.size()].first << " " << robot_purchase_point[robot_num % robot_purchase_point.size()].second << endl;
			}
			else
			{
				no_buy = true;
			}
		}
	}


	void buy_robot_log()
	{
		if (no_buy)return;
		
		if (money >= 2000)
		{
			
			if (robot_num < 8)
			{
			    cout << "lbot " << robot_purchase_point[robot_num % robot_purchase_point.size()].first << " " << robot_purchase_point[robot_num % robot_purchase_point.size()].second << endl;
				if (robot_num == 7)
				{
					predictable_num.push_back(8);
					edge_frames.push_back(frame_id);
				}
				return;
			}
			vector<pair<double,double>>robot_num_and_efficeincy;
			
			robot_num_and_efficeincy.push_back({0.01,0});
			
			for (int i = 0; i < predictable_num.size(); i++)
			{
				if (frame_id - edge_frames[i] <= 50)
				{
					break;
				}
				cerr << "IMIN"<< robot_num_and_efficeincy.size() << endl;
				double tmp;
				if (i == edge_frames.size() - 1 && frame_id - 1 - edge_frames[i] > 0)
				{
					tmp = 1.0 * (total_accumulate_value[frame_id - 1] - total_accumulate_value[int(edge_frames[i])]) / (frame_id - 1 - edge_frames[i]);
				}
				else
				{
					tmp = 1.0 * (total_accumulate_value[int(edge_frames[i + 1])] - total_accumulate_value[int(edge_frames[i])]) / (edge_frames[i + 1] - edge_frames[i]);
				}
				robot_num_and_efficeincy.push_back(make_pair(predictable_num[i], tmp));
			}
			cerr << "VECTORSIZE" << robot_num_and_efficeincy.size() << endl;
			double a = 0, b = 0;
			for (int i = 0; i < robot_num_and_efficeincy.size(); i++)
			{
				for (int j = 0; j < i; j++)
				{
					cerr << robot_num_and_efficeincy[i].first << ' ' << robot_num_and_efficeincy[i].second << endl;
					cerr << robot_num_and_efficeincy[j].first << ' ' << robot_num_and_efficeincy[j].second << endl;
					pair<double, double>tmp = solvelog(robot_num_and_efficeincy[i], robot_num_and_efficeincy[j] );
					a += tmp.first;
					b += tmp.first;
				}
			}
			a /= (robot_num_and_efficeincy.size() * (robot_num_and_efficeincy.size() - 1) / 2);
			b /= (robot_num_and_efficeincy.size() * (robot_num_and_efficeincy.size() - 1) / 2);
			double predict_efficiency = a * log(robot_num + 1) + b;
			cerr<< a<<' '<<b<<' ' << predict_efficiency << endl;
			if ((predict_efficiency - robot_num_and_efficeincy[robot_num_and_efficeincy.size() - 1].second) * (15000 - frame_id) > 2000)
			{
				if (frame_id - edge_frames[edge_frames.size() - 1] >= 100)
				{
					predictable_num.push_back(robot_num + 1);
					edge_frames.push_back(frame_id);
				}
				cout << "lbot " << robot_purchase_point[robot_num % robot_purchase_point.size()].first << " " << robot_purchase_point[robot_num % robot_purchase_point.size()].second << endl;
			}
			else
			{
				no_buy = true;
			}
		}
	}


	void buy_boat()
	{
		
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
		
		total_accumulate_value[frame_id] = pre_value;
		
		
		boat_option.clear();
		robot_option.clear();
		/*if (money >= 2000 && robot_num < 20)
		{
			cout << "lbot " << robot_purchase_point[robot_num % robot_purchase_point.size()].first << " " << robot_purchase_point[robot_num % robot_purchase_point.size()].second << endl;
			start_record[robot_num + 1] = { frame_id, all_num };
		}*/
		buy_robot_log();

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
		if (total_accumulate_value[frame_id] != 0)
		{
			pre_value = total_accumulate_value[frame_id];
		}
	}
}