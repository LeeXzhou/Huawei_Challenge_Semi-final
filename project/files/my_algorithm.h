#ifndef my_algorithm_h
#define my_algorithm_h
#include "boat.h"
#include "robot.h"
using namespace std;
namespace my_alg {
	void init_dis(); // ���ÿ���㵽10���ۿڵ���̾���
	bool check_valid(const int& x, const int& y);
	bool check_valid(const MyPair& x);
}
#endif // !my_algorithm_h