#include "my_data_structure.h"

// ���� pair �ļӷ������
const MyPair operator+(const MyPair& a, const MyPair& b) {
    int sum_first = a.first + b.first;
    int sum_second = a.second + b.second;
    return MyPair(sum_first, sum_second);
}

// ���� pair �ļ��������
const MyPair operator-(const MyPair& a, const MyPair& b) {
    int diff_first = a.first - b.first;
    int diff_second = a.second - b.second;
    return MyPair(diff_first, diff_second);
}

// ������������
std::ostream& operator<<(std::ostream& os, const MyPair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
MyTuple::MyTuple() : x(-1), y(-1), status(-1) {}
MyTuple::MyTuple(int a, int b, int c) : x(a), y(b), status(c) {}
bool MyTuple::operator<(const MyTuple& tmp) const 
{
    return status < tmp.status;
}

bool MyTuple::operator>(const MyTuple& tmp) const {
    return status > tmp.status;
}
int my_abs(const int& a, const int& b)
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        return b - a;
    }
}
