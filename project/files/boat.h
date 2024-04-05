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
	static bool Clockwise(MyTuple& k);
	static bool AntiClock(MyTuple& k);
	static bool Forward(MyTuple& k);
	static bool operate(MyTuple& t, int op);//0: clockwise, 1: anti, 2:forward
	static bool check_valid(const MyTuple& t);//if this point is valid
	static bool slow_or_not(const MyTuple& t);
	static bool slow_or_not(const MyPair& t);
	void Boat_control();
	int GetId();
	static bool sea_check_valid(int x, int y);
	static bool init_check_valid(int x, int y);
	int cal_manhattan(MyTuple k);
	//private:
	int boat_id, x, y, dir, status, goods_num;

	int target_x = -1, target_y = -1;
<<<<<<< Updated upstream
	bool leave_flag = false;//лч
	static int boat_num;
=======
	bool dept_flag = false;//лч
	int aim_berth = -1; // record the targeted berth, -1 as saling point.
>>>>>>> Stashed changes
	static bool boat_loc[200][200];	//mark the location of ships, any location occupied by any ship is marked true
	static int projection_x[4];
	static int projection_y[4];

	bool visited[200][200][4] = { false };
	MyTuple pre[200][200][4], nxt[200][200][4];

};
extern Boat boat[20];
#endif // !boat_h