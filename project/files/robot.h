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
	bool move_or_not = false;
	Robot() { };
	Robot(int startX, int startY);
};

#endif // !berth_h