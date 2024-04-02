#ifndef berth_h
#define berth_h
#include <queue>
#include <cstring>
#include "my_data_structure.h"

using namespace std;
bool check_boundary(int x, int y);
class Berth {
public:
	int x = -1, y = -1, loading_speed = -1;
	bool aimed = false;
	int num = 0, berth_id = -1;
	Berth() { };
	Berth(int x, int y, int loading_speed);
	MyPair find_goods_from_berth();
	set<MyTuple> goods_info;	//存储该泊位到每个货物的时间，货物x，y坐标，默认time从小到大
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

extern int dis[200][200][10];	//若干个泊位到地图上每个点的距离，有船从海洋走的距离也有机器人从陆地走的距离
#endif // !berth_h
