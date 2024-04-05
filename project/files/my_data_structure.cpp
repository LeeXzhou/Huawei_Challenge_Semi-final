#include "my_data_structure.h"

// 重载 pair 的加法运算符
const MyPair operator+(const MyPair& a, const MyPair& b) {
    int sum_first = a.first + b.first;
    int sum_second = a.second + b.second;
    return MyPair(sum_first, sum_second);
}

// 重载 pair 的减法运算符
const MyPair operator-(const MyPair& a, const MyPair& b) {
    int diff_first = a.first - b.first;
    int diff_second = a.second - b.second;
    return MyPair(diff_first, diff_second);
}

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, const MyPair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

//重载MyTuple的运算符
MyTuple::MyTuple(int a, int b, int c) : x(a), y(b), status(c) {}

bool MyTuple::operator==(const MyTuple& tmp) const  
{
    if (status != tmp.status || x != tmp.x || y != tmp.y)
    {
        return false;
    }
    return true;
}
bool MyTuple::operator<(const MyTuple& tmp) const 
{
    if (status != tmp.status)
    {
        return status < tmp.status;
    }
    else if (x != tmp.x)
    {
        return x < tmp.x;
    }
    else
    {
        return y < tmp.y;
    }
}

bool MyTuple::operator>(const MyTuple& tmp) const {
    if (status != tmp.status)
    {
        return status > tmp.status;
    }
    else if (x != tmp.x)
    {
        return x < tmp.x;
    }
    else
    {
        return y < tmp.y;
    }
}

//重载Foursome的运算符，并提供get_tuple获取前三个元素
Foursome::Foursome(int a, int b, int c, int d) :x(a), y(b), dir(c), flag(d){}
MyTuple Foursome::get_tuple()
{
    return MyTuple(x, y, dir);
}
Plan::Plan(int v, int t, MyPair g)
{
    value = v, time = t, target = g;
}

bool Plan::operator < (const Plan& tmp) const
{
    return value * tmp.time < time * tmp.value;
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

//重载BoatRout
BoatRout::BoatRout(int X, int Y, int Dir, int G_val, int H_val) : x(X), y(Y), dir(Dir), g_val(G_val), h_val(H_val) {};

bool BoatRout::operator < (const BoatRout& tmp) const {
    return g_val + h_val > tmp.g_val + tmp.h_val;
}

int Manhattan(const MyPair & a, const MyPair & b) {
    return my_abs(a.first, b.first) + my_abs(a.second, b.second);
}