#ifndef robot_h
#define robot_h
#include <queue>
#include <cstring>
#include "berth.h"
using namespace std;

class Robot {
public:
	int x = -1, y = -1, robot_id = -1, goods_num = -1;
	int status = -1;
	int target_x = -1, target_y = -1;
	MyPair pre[200][200], nxt[200][200];
	bool visited[200][200] = { false };
	bool move_or_not = false, no_goods = false;
	Robot() { };
	Robot(int startX, int startY);
	void find_goods();
	void get_nxt(MyPair & target);
	void find_berth();
	void find_road(const int& min_dis);
	void clash_solve();
	bool robot_dfs(const int& move_num, stack<MyPair>move_order);
	void robot_control();

	static bool land_check_valid(const int& x, const int& y);
	static bool land_check_valid(const MyPair& x);
};
extern Robot robot[30];
#endif // !berth_h
