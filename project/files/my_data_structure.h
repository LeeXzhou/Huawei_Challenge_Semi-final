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

struct MyTuple {
	int x, y, status;
	MyTuple();
	MyTuple(int a = -1, int b = -1, int c = -1);
	bool operator<(const MyTuple& tmp) const;
	bool operator>(const MyTuple& tmp) const;
};

int my_abs(const int& a, const int& b);
#endif // !my_data_structure_h
