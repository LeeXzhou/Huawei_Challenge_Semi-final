#ifndef boat_h
#define boat_h
#include "berth.h"
#include <queue>
#include <cstring>

using namespace std;
class Boat {
public:
	Boat(int id = -1, int X = -1, int Y = -1, direction Dir = east/*east as default*/, int Status = -1, int Num_goods = 0);
	void find_road();
	void find_road2();
	static bool operate(MyTuple& t, int op);//0: clockwise, 1: anti, 2:forward
	static bool check_valid(const MyTuple& t);//if this point is valid
	static bool slow_or_not(const MyTuple& t);
	static bool slow_or_not(const MyPair& t);
	void Boat_control();
	void choose_berth();	//挑选货物量最多的泊位
	void clash_solve(int op, MyTuple boat_a);
	static bool two_boat_clash(MyTuple a, MyTuple b);//判断两个三元组是否冲突
	int GetId();
	static bool sea_check_valid(int x, int y);
	static bool init_check_valid(int x, int y);
	int cal_manhattan(MyTuple k);
	//private:
	int boat_id, x, y, dir, status, goods_num;

	int target_x = -1, target_y = -1;
	bool dept_flag = false;//坨
	int aim_berth = -1;
	int aim_delivery = -1;
	static int projection_x[4], projection_y[4];
	static int operation[6][3];
	bool dept_or_not = false;
	bool visited[200][200][4] = { false };
	MyTuple pre[200][200][4], nxt[200][200][4];
};
extern Boat boat[20];
const int fx[4] = { 0, 0, -1, 1 };
const int fy[4] = { 1, -1, 0, 0 };
const int rot_0x[4] = { 0,0,-2,2 };
const int rot_0y[4] = { 2,-2,0,0 };
const int rot_1x[4] = { 1,-1,-1,1 };
const int rot_1y[4] = { 1,-1,1,-1 };
const int rot_0dir[4] = { 3,2,0,1 };
const int rot_1dir[4] = { 2,3,1,0 };
#endif // !boat_h