#ifndef my_algorithm_h
#define my_algorithm_h
#include "boat.h"
#include "robot.h"
using namespace std;
namespace my_alg {
	void init_dis(); // 求出每个点到10个港口的最短距离
	void test_robot();
	void get_left_num();
}
#endif // !my_algorithm_h