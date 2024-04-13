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
	int left_num = 0;
	int nearest_delivery = 0; // ������������
	int nearest_delivery_point = 0;// �����������
	int end_time = 15000; // ����ʱ��
	Berth() { };
	Berth(int x, int y, int loading_speed);
	MyPair find_goods_from_berth();
	set<MyTuple> goods_info;	//�洢�ò�λ��ÿ�������ʱ�䣬����x��y���꣬Ĭ��time��С����
};

const int N = 200, boat_price = 8000, robot_price = 2000;
const MyPair dx_dy[4] = { {0, 1} , {0, -1}, {-1, 0}, {1, 0} };

extern int robot_num, boat_num, berth_num, delivery_num, goods_num;
extern int frame_id;
extern int money, boat_capacity, all_num;
extern double sum_efficiency[30], predict_efficiency[30], sum_value;
extern MyPair start_record[30];
extern char grid[N][N];
extern MyPair goods_map[N][N];
extern vector<MyPair> robot_purchase_point, boat_purchase_point, delivery_point;
extern Berth berth[10];
extern vector<string> boat_option, robot_option;
extern int land_dis[200][200][15], sea_dis[200][200][10];	//���ɸ���λ����ͼ��ÿ����ľ���(½��)
extern int delivery_dis[200][200][5], berth_dis[200][200][10], delivery_dis_four[200][200][5][4];
extern int robot_num_max, boat_num_max;
extern vector<set<MyTuple>> lbot_goods_info;
#endif // !berth_h