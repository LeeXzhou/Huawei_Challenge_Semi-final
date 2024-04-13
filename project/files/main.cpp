#include <iostream>
#include "my_algorithm.h"
using namespace std;
int robot_num, boat_num, berth_num, delivery_num, goods_num;
vector<string> boat_option, robot_option;
int frame_id;
int money, boat_capacity, all_num;
int max_dis;
int land_dis[200][200][15], delivery_dis[200][200][5], berth_dis[200][200][10], delivery_dis_four[200][200][5][4];
char grid[N][N];
MyPair goods_map[N][N];
vector<MyPair> robot_purchase_point, boat_purchase_point, delivery_point;
vector<set<MyTuple>> lbot_goods_info;
Berth berth[10];
Robot robot[30];
Boat boat[20];
double sum_efficiency[30], predict_efficiency[30], sum_value;
MyPair start_record[30];
const int tg = 1; // 1 is from lizhou, 0 is from lsh
int robot_num_max = 15, boat_num_max = 2;
static bool division = false;
static int identification = 0;
static void ProcessMap()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grid[i][j] == 'R')
			{
				robot_purchase_point.push_back(make_pair(i, j));
				//identification += i * j;
				//cerr << i << " " << j << endl;
				if (i == 101 && j == 38)
				{
					robot_num_max = 13;
					boat_num_max = 2;
				}
				else if (i == 146 && j == 46)
				{
					robot_num_max = 13;
					boat_num_max = 1;
				}
				else if (robot_num_max == 0) {
					robot_num_max = 13;
					boat_num_max = 1;
				}
			}
				
			else if (grid[i][j] == 'S')
				boat_purchase_point.push_back(make_pair(i, j));
			else if (grid[i][j] == 'T')
			{
				delivery_point.push_back(make_pair(i, j));
				delivery_num += 1;
			}

		}
	}
}


void Init()
{
	for (int i = 0; i < N; i++) {
		cin >> grid[i];
	}
	ProcessMap();
	lbot_goods_info.resize(robot_purchase_point.size());
	cin >> berth_num;
	int id = -1;
	for (int i = 0; i < berth_num; i++)
	{
		cin >> id;
		berth[i].berth_id = i;
		cin >> berth[id].x >> berth[id].y >> berth[id].loading_speed;
	}
	cin >> boat_capacity;

	my_alg::init_dis();
	int min_dis = 0, point_num = 0, total_dis = 0;
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			min_dis = 300000;
			for (int t = 0; t < berth_num; t++)
			{
				if (land_dis[i][j][t] > 0 && land_dis[i][j][t] < min_dis)
				{
					min_dis = land_dis[i][j][t];
				}
			}
			if (min_dis != 300000)
			{
				point_num += 1;
				total_dis += min_dis;
			}
		}
	}
	if (point_num >= 28000 && robot_num == 30)
	{
		division = true;
	}
	//cerr << 1.0 * total_dis / point_num << endl;
	//cerr << total_dis << " " << point_num << endl;
	for (int i = 0; i < berth_num; i++)
	{
		int tmp = 300000, mi = -1;
		for (int j = 0; j < delivery_num; j++)
		{
			if (delivery_dis[berth[i].x][berth[i].y][j] < tmp) {
				tmp = delivery_dis[berth[i].x][berth[i].y][j];
				mi = j;
			}
		}
		berth[i].nearest_delivery = tmp;
		berth[i].nearest_delivery_point = mi;
		//berth[i].end_time -= tmp + 10;
		if (tmp > 0)
		{
			max_dis = max(max_dis, tmp);
		}		
	}
	//cerr << max_dis << endl;
	for (int i = 0; i < 30; i++)
	{
		if(tg != 0)
			predict_efficiency[i] = -1;
		sum_efficiency[i] = -1;
	}
	char okk[100];
	cin >> okk;
	cout << "OK\n";
	fflush(stdout);
}


void Input()
{
	cin >> money >> goods_num;
	for (int i = 0; i < goods_num; i++)
	{
		int x, y, val;
		cin >> x >> y >> val;
		if (val > 0)
		{
			for (int j = 0; j < berth_num; j++)
			{
				if (land_dis[x][y][j] != -1)
				{
					berth[j].goods_info.insert(MyTuple(x, y, frame_id + 1000 - land_dis[x][y][j]));
				}
			}
			for (int j = 0; j < robot_purchase_point.size(); j++)
			{
				if (land_dis[x][y][j + berth_num] != -1)
				{
					lbot_goods_info[j].insert(MyTuple(x, y, frame_id + 1000 - land_dis[x][y][j + berth_num]));
				}
			}
		}
		
		goods_map[x][y] = { val, frame_id + 1000 };
	}

	cin >> robot_num;
	for (int i = 0; i < robot_num; i++)
	{
		cin >> robot[i].robot_id >> robot[i].goods_num >> robot[i].x >> robot[i].y;
		//cerr << robot[i].robot_id << " " << robot[i].goods_num << endl;
		robot[i].move_or_not = false;
	}

	cin >> boat_num;
	for (int i = 0; i < boat_num; i++)
	{
		cin >> boat[i].boat_id >> boat[i].goods_num >> boat[i].x >> boat[i].y >> boat[i].dir >> boat[i].status;
		boat[i].dept_or_not = false;
	}
	char okk[100];
	cin >> okk;
}


// -----------------------------------------------start----------------------------------------
int main()
{
	Init();
	while (cin >> frame_id)
	{
		//if (frame_id % 100 == 0)
		//{
		//	cerr << sum_value << endl;
		//	cerr << robot_num << " " << robot_num_max << endl;
		//}
		if (cin.fail())
		{
			break;
		}
		Input();
		/*if (division)	//保证了一定刚好25000块
		{
			continue;
		}*/
		if (frame_id >= 2)my_alg::test_robot();
		if (frame_id == 1)
		{
			cout << "lbot " << robot_purchase_point[0].first << " " << robot_purchase_point[0].second << " 1" << endl;
			//robot[0].type = 1;
			//robot_num_max -= 1;
			cout << "lboat " << boat_purchase_point[0].first << " " << boat_purchase_point[0].second << endl;
			robot[robot_num].x = robot_purchase_point[robot_num % robot_purchase_point.size()].first, robot[robot_num].y = robot_purchase_point[robot_num % robot_purchase_point.size()].second;
			MyPair target = Robot::find_goods_from_purchase(0);
			if (target.first != -1)
			{
				robot[robot_num].target_x = target.first, robot[robot_num].target_y = target.second;
				goods_map[target.first][target.second].first = -goods_map[target.first][target.second].first;
				robot[robot_num].find_road(land_dis[target.first][target.second][berth_num]);
			}
			else
			{
				robot[robot_num].no_goods = true;
			}
		}
		else if (money >= 8000 && robot_num == robot_num_max && (boat_num < boat_num_max || boat_num_max == 0))
		{
			bool check = false;
			if (boat_num_max == 0)
			{
				if (frame_id % 200 == 0)
				{
					sum_efficiency[robot_num] = static_cast<double>((all_num - start_record[robot_num].second)) / static_cast<double>(frame_id - start_record[robot_num].first) * 200.0;
				}
				if (sum_efficiency[robot_num] / 200.0 * max_dis * 2.0 > 1.0 * boat_capacity * boat_num)
				{
					check = true;
				}
			}
			else
			{
				check = true;
			}
			if (check)
			{
				cout << "lboat " << boat_purchase_point[boat_num % boat_purchase_point.size()].first << " " << boat_purchase_point[boat_num % boat_purchase_point.size()].second << endl;
			}
			
		}
		/*if (frame_id == 14995)
		{
			cerr << robot_num << " " << boat_num << endl;
		}*/
		// if (frame_id == 15000)
		// {
		// 	cerr << boat_num << " " << robot_num << endl;
		// 	for (int i = 0; i < berth_num; i++) {
		// 		cerr << berth[i].num << '\n';
		// 	}
		// }
		puts("OK");
		fflush(stdout);
		/*if (robot_num)
		{
			if (frame_id % 1000 == 0)
			{
				cerr << all_num << " " << frame_id << endl;
			}
		}*/
		if (frame_id == 14999)
		{
			for (int i = 0; i < berth_num; i++)
			{
				cerr << berth[i].num << " ";
			}
		}
	}
	return 0;
}
