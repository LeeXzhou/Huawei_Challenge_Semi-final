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

//����MyTuple�������
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

//����Foursome������������ṩget_tuple��ȡǰ����Ԫ��
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

//����BoatRout
BoatRout::BoatRout(int X, int Y, int Dir, int G_val, int H_val) : x(X), y(Y), dir(Dir), g_val(G_val), h_val(H_val) {};

bool BoatRout::operator < (const BoatRout& tmp) const {
    return g_val + h_val > tmp.g_val + tmp.h_val;
}

int Manhattan(const MyPair & a, const MyPair & b) {
    return my_abs(a.first, b.first) + my_abs(a.second, b.second);
}