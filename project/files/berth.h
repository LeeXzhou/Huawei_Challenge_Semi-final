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
	int left_num = 0;
	queue<int>goods_queue;
	Berth() { };
	Berth(int x, int y, int loading_speed);
	MyTuple find_goods_from_berth();
	set<MyTuple> goods_info;	//存储该泊位到每个货物的时间，货物x，y坐标，默认time从小到大
};

const int N = 200, boat_price = 8000, robot_price = 2000;
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };


extern double total_accumulate_value[15005];
extern double pre_value;
extern vector<double>predictable_num;
extern vector<double>predictable_total_efficiency_perframe;
extern vector<double>edge_frames;
extern bool no_buy;
extern bool no_buy_boat;


extern int robot_num, boat_num, berth_num, delivery_num, goods_num;
extern int frame_id;
extern int money, boat_capacity, all_num;
extern double sum_efficiency[30], predict_efficiency[30], sum_value;
extern MyPair start_record[30];
extern char grid[N][N];
extern MyPair goods_map[N][N];
extern vector<MyPair> robot_purchase_point, boat_purchase_point, delivery_point;
extern Berth berth[10];
extern vector<string> boat_option, robot_option;
extern int land_dis[200][200][10], sea_dis[200][200][10];	//若干个泊位到地图上每个点的距离(陆地)
extern int delivery_dis[200][200][5], berth_dis[200][200][10];
#endif // !berth_h
