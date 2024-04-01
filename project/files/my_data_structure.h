#ifndef my_data_structure_h
#define my_data_structure_h
#include <utility>
#include <iostream>
#include <memory>
#include <stack>
#include <cstring>
#include <random>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
using MyPair = std::pair<int, int>;

// 重载 pair 的加法运算符
const MyPair operator+(const MyPair& a, const MyPair& b);

// 重载 pair 的减法运算符
const MyPair operator-(const MyPair& a, const MyPair& b);

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, const MyPair& p);

struct Plan {
	int value = 0, time = 0, robot_id;
	MyPair target;
	Plan(int v, int t, int i, MyPair g);
	bool operator < (const Plan& tmp) const;
};
struct Record {
	int time = -1, cur_x = -1, cur_y = -1;
	Record(int t, int x, int y);
	bool operator < (const Record& tmp) const;
};

int my_abs(const int& a, const int& b);
#endif // !my_data_structure_h
