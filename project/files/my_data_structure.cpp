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
vector<double>lagrange(vector<double>x, vector<double>y, vector<double>input_x)
{
    vector<double>output_y;
    for (int u = 0; u < input_x.size(); u++)
    {
        double output = 0;
        for (int i = 0; i < x.size(); i++)
        {
            double tmp = y[i];
            for (int j = 0; j < x.size(); j++)
            {
                if (i == j)continue;
                tmp *= (input_x[u] - x[j]) / (x[i] - x[j]);
            }
            output += tmp;
        }
        output_y.push_back(output);
    }
    return output_y;
}

pair<double, double> solvelog(pair<double, double> a, pair<double, double> b)
{
    double retx = 1.0 * (a.second - b.second) / (log(a.first) - log(b.first));
    //cerr << "TEETTETEYT" << a.second - b.second <<' ' << log(a.first) - log(b.first) <<' '<<retx<< endl;
    double rety = 1.0 * a.second - retx * log(a.first);
    return make_pair(retx, rety);
}

double predict_log(vector<double>x, vector<double>y, double predict_num)
{
    double a = 0, b = 0;
    int fenzi = 0;
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            
            pair<double, double>tmp = solvelog(make_pair(x[i], y[i]), make_pair(x[j], y[j]));
            a += tmp.first;
            b += tmp.second;
        }
    }
    a = 1.0 * a / ((x.size() - 1) * x.size() / 2);
    b = 1.0 * b / ((x.size() - 1) * x.size() / 2);
    double ans = a * log(predict_num) + b;
    return ans;
}