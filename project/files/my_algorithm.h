#ifndef my_algorithm_h
#define my_algorithm_h
#include "boat.h"
#include "robot.h"
using namespace std;
namespace my_alg {
	void init_dis(); // 求出每个点到10个港口的最短距离
	void test_robot();
	void predict();
	void get_left_num();
	bool buy_robot();
	void function_predict();
	double fun(int i);
	static bool no_buy = false;
}
#endif // !my_algorithm_h