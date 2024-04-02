#ifndef berth_h
#define berth_h
#include <queue>
#include <cstring>
#include "my_data_structure.h"

using namespace std;
bool check_boundary(int x, int y);
class Berth {
public:
	int x = -1, y = -1, loading_speed = -1;
	bool aimed = false;
	int num = 0, berth_id = -1;
	Berth() { };
	Berth(int x, int y, int loading_speed);
	MyPair find_goods_from_berth();
	set<MyTuple> goods_info;	//�洢�ò�λ��ÿ�������ʱ�䣬����x��y���꣬Ĭ��time��С����
};

const int N = 200, boat_price = 8000, robot_price = 2000;
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };

extern int robot_num, boat_num, berth_num, goods_num;
extern int frame_id;
extern int money, boat_capacity;

extern char grid[N][N];
extern MyPair goods_map[N][N];
extern vector<pair<int, int>> robot_purchase_point;
extern vector<pair<int, int>> boat_purchase_point;
extern vector<pair<int, int>> delivery_point;
extern Berth berth[10];

extern int dis[200][200][10];	//���ɸ���λ����ͼ��ÿ����ľ��룬�д��Ӻ����ߵľ���Ҳ�л����˴�½���ߵľ���
#endif // !berth_h
