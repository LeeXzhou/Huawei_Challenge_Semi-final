#ifndef robot_h
#define robot_h
#include <queue>
#include <cstring>
#include "berth.h"
using namespace std;

class Robot {
public:
	int x = -1, y = -1, robot_id = -1, goods_num = -1;
	int target_x = -1, target_y = -1;	//目标地，-1为没目标
	MyPair pre[200][200], nxt[200][200];
	bool visited[200][200] = { false };
	bool move_or_not = false, no_goods = false;	//是否移动，true为这帧移动过了，地图上是否还有货物，true为没有货物
	bool end_of_robot = false;
	int target_berth = -1;
	Robot() { };
	Robot(int startX, int startY);
	void find_goods();	//bfs到至多6个货物，然后选取货物
	void get_nxt(MyPair & target);	//利用pre找nxt
	void find_berth();	//从当前位置去找最近的泊位
	void find_road(const int& min_dis);	//利用min_dis剪枝来找路
	void clash_solve();	//机器人移动，包括了防碰撞
	bool robot_dfs(const int& move_num, stack<MyPair>move_order);	//用来解决防碰撞
	void robot_control();	//控制机器人

	static MyPair find_goods_from_purchase(int cur_pos);
	static bool land_check_valid(const int& x, const int& y);	//是否可移动到
	static bool land_check_valid(const MyPair& x);
};
extern Robot robot[30];
#endif // !berth_h
