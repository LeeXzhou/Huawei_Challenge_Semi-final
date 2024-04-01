#include <iostream>
#include "record.h"
using namespace std;

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
    for (int i = 0; i < berth_num; i++)
    {
        int id;
        cin >> id >> berth[id].x >> berth[id].y >> berth[id].loading_speed;
    }
    cin >> boat_capacity;
    char okk[100];
    cin >> okk;
    cout << "OK\n";
    fflush(stdout);
}


int Input()
{
    cin >> money >> goods_num;
    for (int i = 0; i < goods_num; i++)
    {
        int x, y, val;
        cin >> x >> y >> val;
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