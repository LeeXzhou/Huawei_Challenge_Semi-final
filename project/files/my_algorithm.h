#ifndef my_algorithm_h
#define my_algorithm_h
#include "boat.h"
#include "robot.h"
using namespace std;
namespace my_alg {
	void init_dis(); // ���ÿ���㵽10���ۿڵ���̾���
	void test_robot();
	void predict();
	void get_left_num();
	bool buy_robot();
	static bool no_buy = false;
}
#endif // !my_algorithm_h