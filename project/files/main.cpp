#include <iostream>
#include "my_algorithm.h"
using namespace std;
int robot_num, boat_num, berth_num, delivery_num, goods_num;
vector<string> boat_option, robot_option;
int frame_id;
int money, boat_capacity, all_num;
int land_dis[200][200][10], delivery_dis[200][200][5];
char grid[N][N];
MyPair goods_map[N][N];
vector<MyPair> robot_purchase_point, boat_purchase_point, delivery_point;
Berth berth[10];
Robot robot[30];
Boat boat[20];
void ProcessMap()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grid[i][j] == 'R')
				robot_purchase_point.push_back(make_pair(i, j));
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
	/*for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			cerr << dis[i][j][0] << " ";

		}cerr << endl;
	}*/
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
		for (int j = 0; j < berth_num; j++)
		{
			if (land_dis[x][y][j] != -1)
			{
				berth[j].goods_info.insert(MyTuple(x, y, frame_id + 1000 - land_dis[x][y][j]));
			}
		}
		goods_map[x][y] = { val, frame_id + 1000 };
	}

	cin >> robot_num;
	for (int i = 0; i < robot_num; i++)
	{
		cin >> robot[i].robot_id >> robot[i].goods_num >> robot[i].x >> robot[i].y;
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
		//cerr << frame_id << endl;
		if (cin.fail())
		{
			break;
		}
		Input();
		if (frame_id >= 2)my_alg::test_robot();
		if (frame_id == 1)
		{
			cout << "lboat " << boat_purchase_point[0].first << " " << boat_purchase_point[0].second << endl;
		}
		else if (money >= 8000 && robot_num == 20 && boat_num < 2)
		{
			cout << "lboat " << boat_purchase_point[0].first << " " << boat_purchase_point[0].second << endl;
		}
		puts("OK");
		fflush(stdout);
		if (robot_num)
		{
			if (frame_id % 1000 == 0)
			{
				cerr << all_num << " " << frame_id << endl;
			}
		}
	}
	return 0;
}