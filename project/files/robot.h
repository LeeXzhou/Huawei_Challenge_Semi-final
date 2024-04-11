#ifndef robot_h
#define robot_h
#include <queue>
#include <cstring>
#include "berth.h"
using namespace std;

class Robot {
public:
	int x = -1, y = -1, robot_id = -1, goods_num = -1;
	int target_x = -1, target_y = -1;	//Ŀ��أ�-1ΪûĿ��
	MyPair pre[200][200], nxt[200][200];
	bool visited[200][200] = { false };
	int carry_value = 0;
	double eps_value=0;
	double accumulate_value=0;
	bool move_or_not = false, no_goods = false;	//�Ƿ��ƶ���trueΪ��֡�ƶ����ˣ���ͼ���Ƿ��л��trueΪû�л���
	Robot() { };
	Robot(int startX, int startY);
	void find_goods();	//bfs������6�����Ȼ��ѡȡ����
	void get_nxt(MyPair & target);	//����pre��nxt
	int find_berth();	//�ӵ�ǰλ��ȥ������Ĳ�λ
	void find_road(const int& min_dis);	//����min_dis��֦����·
	void clash_solve();	//�������ƶ��������˷���ײ
	bool robot_dfs(const int& move_num, stack<MyPair>move_order);	//�����������ײ
	void robot_control();	//���ƻ�����

	static bool land_check_valid(const int& x, const int& y);	//�Ƿ���ƶ���
	static bool land_check_valid(const MyPair& x);
};
extern Robot robot[30];
#endif // !berth_h
