#ifndef boat_h
#define boat_h
#include "berth.h"
#include <queue>
#include <cstring>

using namespace std;
class Boat {
public:
	int boat_id = -1, x = -1, y = -1, dir = -1;
	int goods_num = 0, status = -1;
	Boat() { };
};

#endif // !boat_h
