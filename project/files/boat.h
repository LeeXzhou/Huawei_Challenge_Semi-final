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


	bool slow_or_not(const MyPair& t);
	bool slow_or_not(const MyTuple& t);
	static bool Clockwise(int x, int y, direction dir);
	static bool AntiClock(int x, int y, direction dir);
	static bool Forward(int x, int y, direction dir);
	static bool operate(MyTuple &t, int op);//0: clockwise, 1: anti, 2:forward
	static bool check_valid(int x, int y, direction dir);//ÊÇ·ñ¿ÉÐÐ
	void Boat_control();
	int GetId();
	static bool sea_check_valid(int x, int y);
	static bool init_check_valid(int x, int y);
	static void init_boat_loc();
	//private:
	int boat_id, x, y, dir, status, goods_num;

	int target_x, target_y;

	static int boat_num;
	static bool boat_loc[200][200];	//mark the location of ships, any location occupied by any ship is marked true
	static int projection_x[4];
	static int projection_y[4];

	bool visited[200][200][4] = { false };
	MyTuple pre[200][200][4], nxt[200][200][4];

};

#endif // !boat_h
