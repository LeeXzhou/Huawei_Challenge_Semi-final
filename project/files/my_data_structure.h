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

enum direction {
	north = 0,
	south = 2,
	west = 3,
	east = 1
};

// ���� pair �ļӷ������
const MyPair operator+(const MyPair& a, const MyPair& b);

// ���� pair �ļ��������
const MyPair operator-(const MyPair& a, const MyPair& b);

// ������������
std::ostream& operator<<(std::ostream& os, const MyPair& p);

struct MyTuple {
	int x, y, status;

	MyTuple(int a = -1, int b = -1, int c = -1);
	bool operator<(const MyTuple& tmp) const;
	bool operator>(const MyTuple& tmp) const;
};

struct Foursome {
	int x, y, dir, flag;
	
	Foursome(int a=-1, int b=-1, int c=-1, int d=-1);
};
struct Plan {
	int value = 0, time = 0;
	MyPair target;
	Plan(int v, int t, MyPair g);
	bool operator < (const Plan& tmp) const;
};

int my_abs(const int& a, const int& b);
#endif // !my_data_structure_h
