#ifndef record_h
#define record_h
#include <queue>
#include <cstring>
#include "my_data_structure.h"

using namespace std;
bool check_valid(const int& x, const int& y);
bool check_valid(const MyPair& x);
const int round_robot_num(const int& x, const int& y);
class Robot {
public:
	int x = -1, y = -1, robot_id = -1, goods_num = -1;
	int status = -1;
	int target_x = -1, target_y = -1;
	MyPair pre[200][200], nxt[200][200];
	bool visited[200][200] = { false };
	bool move_or_not = false;
	Robot() { };
	Robot(int startX, int startY);
	void robot_control();
	void find_goods();
	void find_berth();
	void find_road(const int& min_dis);
	void clash_solve();
	bool robot_dfs(const int& move_num, stack<MyPair>move_order);
};

class Berth {
public:
	int x = -1, y = -1, loading_speed = -1;
	bool aimed = false;
	int num = 0, berth_id = -1;
	int close_time = 15000;
	Berth() { };
	Berth(int x, int y, int loading_speed);
	MyPair find_goods_from_berth();
	set<Record> goods_info;	//存储该泊位到每个货物的时间，货物x，y坐标，默认time从小到大
};

class Boat {
public:
	int boat_id = -1, x = -1, y = -1, dir = -1;
	int goods_num = 0, status = -1;

	int tail_status = -1;
	int aim_berth = -1, left_time = -1;
	Boat() { };
	void boat_control();
};
const int N = 200;

extern int robot_num = 0;
extern int boat_num = 0;
extern int berth_num = 0;

extern int goods_num = 0;
extern int frame_id = 0;
extern int money, boat_capacity, boat_price = 8000, robot_price = 2000;

extern char grid[N][N];
extern MyPair goods_map[N][N];
extern vector<pair<int, int>> robot_purchase_point;
extern vector<pair<int, int>> boat_purchase_point;
extern vector<pair<int, int>> delivery_point;
extern Berth berth[10];
extern Robot robot[20];
extern Boat boat[20];
#endif // !record_h
