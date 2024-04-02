#include "robot.h"
using namespace std;
bool Robot::land_check_valid(const int& x, const int& y)
{
	if (check_boundary(x, y))
	{
		if (grid[x][y] == '.' || grid[x][y] == '>' || grid[x][y] == 'R' || grid[x][y] == 'B' || grid[x][y] == 'C' || grid[x][y] == 'c')
		{
			return true;
		}
	}
	return false;
}

bool Robot::land_check_valid(const MyPair& x)
{
	return land_check_valid(x.first, x.second);
}
Robot::Robot(int startX, int startY) {
	x = startX;
	y = startY;
}

void Robot::robot_control()
{
	if (move_or_not)
	{
		return;
	}
	if (target_x == -1)
	{
		//定个目标地，货物地
		if (goods_num == 0)
		{
			find_goods();
		}
		else
		{
			find_berth();
		}
	}
	clash_solve();
	if (target_x == x && target_y == y)
	{
		//修改目标地
		if (goods_num == 1)	//身上有货物，判断当前位置是不是泊位
		{
			for (int i = 0; i < berth_num; i++)
			{
				if (x >= berth[i].x && x <= berth[i].x + 3 && y <= berth[i].y + 3 && y >= berth[i].y)
				{
					cerr << "in berth " << i << endl;
					cout << "pull " << robot_id << endl;
					berth[i].num += 1;
					target_x = -1;
					target_y = -1;
					MyPair target = berth[i].find_goods_from_berth();
					cerr << target << endl;
					if (target.first == -1)
					{
						find_goods();
					}
					else
					{
						target_x = target.first, target_y = target.second;
						goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
						find_road(dis[target_x][target_y][i]);
					}
					return;
				}
			}
			find_berth();	//找泊位
		}
		else    //身上没有货物，判断当前位置是不是泊位
		{
			for (int i = 0; i < berth_num; i++)	//
			{
				if (x >= berth[i].x && x <= berth[i].x + 3 && y <= berth[i].y + 3 && y >= berth[i].y)
				{
					MyPair target = berth[i].find_goods_from_berth();
					target_x = target.first, target_y = target.second;
					goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
					find_road(dis[target_x][target_y][i]);
					return;
				}
			}
			cout << "get " << robot_id << endl;	//拿货物
			find_berth();	//找泊位
		}
	}
}

void Robot::find_goods()	//只有起始和目的地找货物
{
	if (goods_map[x][y].first > 0 && goods_map[x][y].second > frame_id)
	{
		target_x = x; target_y = y;
		return;
	}
	int cnt = 0;
	memset(pre, 0, sizeof(pre));
	memset(visited, false, sizeof(visited));
	memset(nxt, 0, sizeof(nxt));
	visited[x][y] = true;
	queue<MyPair> q;
	q.push({ x, y });
	bool found = false;
	int step = 0;
	priority_queue<Plan> choice;
	while (cnt < 6 && !q.empty())	//测下来6效果较好
	{
		int q_size = q.size();
		for (int j = 1; j <= q_size; j++)
		{
			MyPair u = q.front();
			q.pop();
			if (goods_map[u.first][u.second].first > 0 && goods_map[u.first][u.second].second - frame_id > step + 1)	//给一点容错
			{
				int good_to_berth_dis = 300000;
				for (int i = 0; i < berth_num; i++)
				{
					if (dis[u.first][u.second][i] > 0)
					{
						good_to_berth_dis = min(good_to_berth_dis, dis[u.first][u.second][i]);
					}
				}
				choice.push(Plan(goods_map[u.first][u.second].first, step + good_to_berth_dis, {u.first, u.second}));
				cnt += 1;
			}

			for (int i = 0; i < 4; i++)
			{
				MyPair tmp = u + dx_dy[i];
				if (land_check_valid(tmp.first, tmp.second) && (!visited[tmp.first][tmp.second]))
				{
					visited[tmp.first][tmp.second] = true;
					pre[tmp.first][tmp.second] = u;
					q.push(tmp);
				}
			}
		}
		step++;
	}
	if (!choice.empty())
	{
		MyPair now = choice.top().target, tmp = { 0, 0 };
		target_x = now.first, target_y = now.second;
		goods_map[target_x][target_y].first = -goods_map[target_x][target_y].first;
		while (tmp.first != x || tmp.second != y)
		{
			tmp = pre[now.first][now.second];
			nxt[tmp.first][tmp.second] = now;
			now = tmp;
		}
	}
	return;
}

void Robot::find_berth() //找泊位
{
	int aim_num = -1;
	int min_dis = 300000;
	for (int i = 0; i < berth_num; i++)
	{
		if (dis[x][y][i] > 0 && dis[x][y][i] < min_dis)
		{
			aim_num = i;
			min_dis = dis[x][y][i];
		}
	}
	if (aim_num == -1)aim_num = 0;
	target_x = berth[aim_num].x;
	target_y = berth[aim_num].y;

	find_road(min_dis);
}

void Robot::find_road(const int& min_dis)	//给定target下去找路
{
	if (x == target_x && y == target_y)
	{
		return;
	}
	memset(pre, 0, sizeof(pre));
	memset(visited, false, sizeof(visited));
	memset(nxt, 0, sizeof(nxt));
	visited[x][y] = true;
	queue<MyPair> q;
	q.push({ x, y });
	bool found = false;
	int step = 0;
	MyPair target = { target_x, target_y };
	while (!found && !q.empty())
	{
		int q_size = q.size();
		for (int j = 1; j <= q_size; j++)
		{
			MyPair u = q.front();
			q.pop();
			if (u == target)
			{
				found = true;
				MyPair now = u, tmp = { 0, 0 };
				while (tmp.first != x || tmp.second != y)
				{
					tmp = pre[now.first][now.second];
					nxt[tmp.first][tmp.second] = now;
					now = tmp;
				}
				break;
			}
			for (int i = 0; i < 4; i++)
			{
				MyPair tmp = u + dx_dy[i];
				if (my_abs(tmp.first, target_x) + my_abs(tmp.second, target_y) > min_dis + 1 - step)
				{
					continue;
				}
				if (land_check_valid(tmp.first, tmp.second) && (!visited[tmp.first][tmp.second]))
				{
					visited[tmp.first][tmp.second] = true;
					pre[tmp.first][tmp.second] = u;
					q.push(tmp);
				}
			}
		}
		step++;
	}
}


bool Robot::robot_dfs(const int& move_num, stack<MyPair>move_order)
{
	if (robot[move_num].move_or_not)return false;
	for (int i = 0; i < 4; i++)
	{
		int ran_i = (i + frame_id) % 4;
		bool robot_clash = false;
		if (!land_check_valid(dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y))) { continue; }
		for (int j = 0; j < robot_num; j++)
		{

			if (move_num == j)continue;
			if (dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y) == make_pair(robot[j].x, robot[j].y))
			{
				robot_clash = true; break;
			}
		}

		if (robot_clash == false)
		{
			move_order.push({ move_num,ran_i });

			while (!move_order.empty())
			{
				MyPair u = move_order.top();
				move_order.pop();
				int u_id = u.first;
				int u_op = u.second;
				robot[u_id].move_or_not = true;

				if (robot[u_id].goods_num == 0)	//存在隐患
				{
					goods_map[robot[u_id].target_x][robot[u_id].target_y].first = -goods_map[robot[u_id].target_x][robot[u_id].target_y].first;
				}
				robot[u_id].target_x = -1;
				robot[u_id].target_y = -1;
				cout << "move " << u_id << " " << u_op << endl;

				robot[u_id].x += dx_dy[u_op].first;
				robot[u_id].y += dx_dy[u_op].second;
				robot[u_id].move_or_not = true;
				if (robot[u_id].goods_num == 0)
				{
					robot[u_id].find_goods();
				}
				else
				{
					robot[u_id].find_berth();
				}

			}
			return true;
		}
	}
	int answer = 0;
	robot[move_num].move_or_not = true;
	for (int i = 0; i < 4; i++)
	{
		int ran_i = (i + frame_id) % 4;
		if (!land_check_valid(dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y)))continue;
		for (int j = 0; j < robot_num; j++)
		{
			if (dx_dy[ran_i] + make_pair(robot[move_num].x, robot[move_num].y) == make_pair(robot[j].x, robot[j].y))
			{
				if (robot[j].move_or_not)continue;
				move_order.push({ move_num,ran_i });
				answer = robot_dfs(j, move_order);
				move_order.pop();
				if (answer == 1)return true;
			}
		}
	}
	robot[move_num].move_or_not = false;
	return false;
}

void Robot::clash_solve()
{
	if (move_or_not)return;
	int flag = 1;
	for (int i = 0; i < robot_num; i++)
	{
		if (i == robot_id)continue;
		if (nxt[x][y] == make_pair(robot[i].x, robot[i].y) && (grid[robot[i].x][robot[i].y] == 'C' || grid[robot[i].x][robot[i].y] == '.' || grid[robot[i].x][robot[i].y] == 'B')) { flag = 0; break; }
	}

	if (flag)//若下一步没有机器人
	{
		MyPair now = { x, y };
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;
				x = nxt[now.first][now.second].first;
				y = nxt[now.first][now.second].second;
				move_or_not = true;


				break;
			}
		}
		return;
	}

	int answer = 0;
	move_or_not = true;
	for (int i = 0; i < robot_num; i++)
	{
		if (nxt[x][y] == make_pair(robot[i].x, robot[i].y))
		{
			stack<MyPair> move_order;
			answer = robot_dfs(i, move_order);
			break;
		}
	}
	if (answer)
	{
		MyPair now = { x, y };
		for (int i = 0; i < 4; i++)
		{
			if (now + dx_dy[i] == nxt[x][y])
			{
				cout << "move " << robot_id << " " << i << endl;

				x = nxt[now.first][now.second].first;
				y = nxt[now.first][now.second].second;
				move_or_not = true;

				break;
			}
		}
	}
	else
	{
		move_or_not = false;
	}

}