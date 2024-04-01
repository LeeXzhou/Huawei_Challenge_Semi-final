#include <iostream>
#include "my_algorithm.h"
using namespace std;
int robot_num, boat_num, berth_num, goods_num;
int frame_id;
int money, boat_capacity;
int dis[200][200][10];
char grid[N][N];
MyPair goods_map[N][N];
vector<pair<int, int>> robot_purchase_point;
vector<pair<int, int>> boat_purchase_point;
vector<pair<int, int>> delivery_point;
Berth berth[10];
Robot robot[30];
Boat boat[20];
void ProcessMap()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'R')
                robot_purchase_point.push_back(make_pair(i, j));
            else if (grid[i][j] == 'S')
                boat_purchase_point.push_back(make_pair(i, j));
            else if (grid[i][j] == 'T')
                delivery_point.push_back(make_pair(i, j));
        }
    }
}


void Init()
{
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    ProcessMap();
    cin >> berth_num;
    int id = -1;
    for (int i = 0; i < berth_num; i++)
    {        
        cin >> id >> berth[id].x >> berth[id].y >> berth[id].loading_speed;
    }
    cin >> boat_capacity;
    char okk[100];
    cin >> okk;
    cout << "OK\n";
    fflush(stdout);
}


void Input()
{
    cin >> money >> goods_num;
    for (int i = 0; i < goods_num; i++)
    {
        int x, y, val;
        cin >> x >> y >> val;
        for (int j = 0; j < berth_num; j++)
        {
            if (dis[x][y][j] != -1)
            {
                berth[j].goods_info.insert(MyTuple(x, y, frame_id));
            }
        }
        goods_map[x][y] = { val, frame_id + 1000 };
    }

    cin >> robot_num;
    for (int i = 0; i < robot_num; i++)
    {
        cin >> robot[i].robot_id >> robot[i].goods_num >> robot[i].x >> robot[i].y;
    }

    cin >> boat_num;
    for (int i = 0; i < boat_num; i++)
    {
        cin >> boat[i].boat_id >> boat[i].goods_num >> boat[i].x >> boat[i].y >> boat[i].dir >> boat[i].status;
    }
    char okk[100];
    cin >> okk;
}


// -----------------------------------------------start----------------------------------------
int main()
{
    Init();
    while (cin >> frame_id)
    {
        if (cin.fail())
        {
            break;
        }
        Input();        

        puts("OK");
        fflush(stdout);
    }
    return 0;
}