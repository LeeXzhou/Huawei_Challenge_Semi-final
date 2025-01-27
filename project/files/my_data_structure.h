#ifndef my_data_structure_h
#define my_data_structure_h
#pragma GCC optimize(2)
#include <utility>
#include <iostream>
#include <memory>
#include <stack>
#include <cstring>
#include <random>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include <thread>
#include <string>
#include<unordered_map>
using namespace std;
using MyPair = std::pair<int, int>;
extern const int tg;	
enum direction {
	north = 2,
	south = 3,
	west = 1,
	east = 0
};

// 重载 pair 的加法运算符
const MyPair operator+(const MyPair& a, const MyPair& b);

// 重载 pair 的减法运算符
const MyPair operator-(const MyPair& a, const MyPair& b);

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, const MyPair& p);

struct MyTuple {
	int x, y, status;
	MyTuple(int a = -1, int b = -1, int c = -1);
	bool operator==(const MyTuple& tmp) const;
	bool operator<(const MyTuple& tmp) const;
	bool operator>(const MyTuple& tmp) const;
};

struct Foursome {
	int x, y, dir, flag;
	MyTuple get_tuple();
	Foursome(int a=-1, int b=-1, int c=-1, int d=-1);
	bool operator > (const Foursome& tmp) const;
};
struct Plan {
	int value = 0, time = 0;
	MyPair target;
	Plan(int v, int t, MyPair g);
	bool operator < (const Plan& tmp) const;
};

int my_abs(const int& a, const int& b);

int Manhattan(const MyPair & a, const MyPair & b);

struct BoatRout {
	int x, y, dir, g_val, h_val;
	BoatRout(int X = -1, int Y = -1, int Dir = -1, int G_val = 0, int H_val = 0);
	bool operator < (const BoatRout& tmp) const;
};
#endif // !my_data_structure_h
