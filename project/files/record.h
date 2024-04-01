#ifndef record_h
#define record_h
#include <queue>
#include <cstring>
#include "my_data_structure.h"

using namespace std;
bool check_valid(const int& x, const int& y);
bool check_valid(const MyPair& x);
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
};

class Berth {
public:
	int x = -1, y = -1, loading_speed = -1;
	bool aimed = false;
	int num = 0, berth_id = -1;
	Berth() { };
	Berth(int x, int y, int loading_speed);
};

class Boat {
public:
	int boat_id = -1, x = -1, y = -1, dir = -1;
	int goods_num = 0, status = -1;
	Boat() { };
};

const int N = 200, boat_price = 8000, robot_price = 2000;
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };

extern int robot_num, boat_num, berth_num, goods_num;
extern int frame_id;
extern int money, boat_capacity;

extern char grid[N][N];
extern MyPair goods_map[N][N];
extern vector<pair<int, int>> robot_purchase_point;
extern vector<pair<int, int>> boat_purchase_point;
extern vector<pair<int, int>> delivery_point;
extern Berth berth[10];
extern Robot robot[20];
extern Boat boat[20];

extern int dis[200][200][10];	//若干个泊位到地图上每个点的距离，有船从海洋走的距离也有机器人从陆地走的距离
#endif // !record_h
