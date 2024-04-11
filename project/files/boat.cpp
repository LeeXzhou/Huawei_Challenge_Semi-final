#include "boat.h"
using namespace std;

int Boat::operation[6][3] = { {0, 1, 2}, {0, 2, 1}, {1, 2, 0}, {1, 0, 2}, {2, 0, 1}, {2, 1, 0} };
// Before create one boat, check if it's valid
Boat::Boat(int id, int X, int Y, direction Dir, int Status, int Num_goods) :
	boat_id(boat_num), x(X), y(Y), dir(Dir), status(Status), goods_num(Num_goods)
{

}

void Boat::Boat_control()
{
	// 恢复状态
	if (status == 1)return;
	if (status == 2) // 装载状态
	{
		if (berth[aim_berth].num > 0 && goods_num < boat_capacity && berth[aim_berth].nearest_delivery + frame_id + 10 < 15000)
		{
			int add = min(berth[aim_berth].loading_speed, min(boat_capacity - goods_num, berth[aim_berth].num));
			goods_num += add;
			berth[aim_berth].num -= add;
			//all_num -= add;
		}
		else
		{
			int min_dis = 300000, target_delivery = 0;
			for (int i = 0; i < delivery_point.size(); i++)
			{
				if (delivery_dis[x][y][i] < min_dis)
				{
					target_delivery = i;
					min_dis = delivery_dis[x][y][i];
				}
			}
			target_x = delivery_point[target_delivery].first;
			target_y = delivery_point[target_delivery].second;
			aim_berth = -1;
			aim_delivery = target_delivery;

			dept_flag = true;
			
			string tmp = "dept " + to_string(boat_id);
			boat_option.push_back(tmp);
			//cerr << "dept " << boat_id << endl;
		}
		return;
	}

	// 行驶状态
	
	if (target_x == -1)
	{
		// 最初始状态
		choose_berth();
		find_road2();
		return;
	}

		// 到达指定地点
		if (target_x == x && target_y == y)
		{
			if (x == berth[aim_berth].x && y == berth[aim_berth].y)
			{
				// 到了港口
				string tmp = "berth " + to_string(boat_id);
				boat_option.push_back(tmp);
				//cout << "berth " << boat_id << endl;;
			}
			else
			{
				// 到了交货点
				choose_berth();
				cerr << "in\n";
				find_road2();
				cerr << "out\n";
			}
			return;
		}
		if (dept_flag == true)
		{
			int min_dis = 300000, target_delivery = 0;
			for (int i = 0; i < delivery_num; i++)
			{
				if (delivery_dis[x][y][i] < min_dis)
				{
					min_dis = delivery_dis[x][y][i];
					target_delivery = i;
				}
			}
			if (goods_num < boat_capacity && 15000 - frame_id > min_dis + 10)	//解决尾杀
			{
				choose_berth();
			}
			else
			{
				target_x = delivery_point[target_delivery].first;
				target_y = delivery_point[target_delivery].second;
			}
			find_road2();
			dept_flag = false;
			return;
		}
		for (int j = 0; j <= 2; j++)
		{
			MyTuple tmp = MyTuple(x, y, dir);
			if (operate(tmp, j)) {
				if (tmp == nxt[x][y][dir]) {
					clash_solve(j, tmp);
					
					if (aim_berth != -1) {
						int mi = 300000, tmp = -1;
						for (int i = 0; i < delivery_num; i++)
						{
							if (mi > delivery_dis[x][y][i]) {
								mi = delivery_dis[x][y][i];
								tmp = i;
							}
						}
						if ((delivery_dis[x][y][tmp] < 5 && goods_num > 20) || (mi + frame_id + 10 > 15000))
						{
							target_x = delivery_point[tmp].first;
							target_y = delivery_point[tmp].second;
							find_road2();
							aim_berth = -1;
							aim_delivery = tmp;
							return;
						}
					}
				}
			}
		}
}
// repeat this function check before and after move, which can be improved
bool Boat::slow_or_not(const MyPair& t) {
	int x = t.first, y = t.second;
	char tmp = grid[x][y];
	return tmp == '~' || tmp == 'S' || tmp == 'c' || tmp == 'B' || tmp == 'K' || tmp == 'T';
}

bool Boat::slow_or_not(const MyTuple& t) {
	int x = t.x, y = t.y, dir = t.status;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if ((dir == 2 && slow_or_not(make_pair(x - j, y + i))) ||
				(dir == 3 && slow_or_not(make_pair(x + j, y - i))) ||
				(dir == 1 && slow_or_not(make_pair(x - i, y - j))) ||
				(dir == 0 && slow_or_not(make_pair(x + i, y + j)))) {
				return true;
			}
		}
	}
	return false;
}



bool Boat::sea_check_valid(int x, int y) {//yes if valid
	if (!check_boundary(x, y)) return false;
	char tmp = grid[x][y];
	//if (boat_loc[x][y]) // there is a ship
	//	return tmp == '~' || tmp == 'S' || tmp == 'c' || tmp == 'B' || tmp == 'K' || tmp == 'T';
	return tmp == '*' || tmp == '~' || tmp == 'S' || tmp == 'c' || tmp == 'B' || tmp == 'K' || tmp == 'T' || tmp == 'C';
}

bool Boat::init_check_valid(int x, int y) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (!sea_check_valid(i, j))
				return false;
		}
	}
	return true;
}

void Boat::find_road()
{
	//cerr << "in!" << endl;
	if (x == target_x && y == target_y) return;
	memset(pre, 0, sizeof(pre)); memset(nxt, 0, sizeof(nxt)); memset(visited, false, sizeof(visited));

	queue<Foursome>q;
	if (slow_or_not(MyTuple(x, y, dir)))//如果初始点包含主航道
	{
		q.push(Foursome(x, y, dir, 0));
	}
	else
	{
		visited[x][y][dir] = true;
		q.push(Foursome(x, y, dir, 1));
	}
	bool found = false;
	int step = 0;
	//cerr << target_x << " " << target_y << endl;
	while (!found && !q.empty())
	{
		//cerr << "see see\n";
		//cerr << frame_id << endl;
		int q_size = q.size();
		for (int i = 1; i <= q_size; i++)
		{
			if (frame_id >= 70 && frame_id <= 120)cerr << step << endl;
			//cerr << step << '\n';
			Foursome u = q.front();


			q.pop();
			//cerr << u.x << " " << u.y <<' '<<u.dir<< endl;
			if (u.x == target_x && u.y == target_y)
			{
				found = true;
				//cerr << "GFUcsggfjszfdss" << endl;

				MyTuple now = MyTuple(u.x, u.y, u.dir), tmp = MyTuple(0, 0, 0);
				while (tmp.x != x || tmp.y != y || tmp.status != dir)
				{

					tmp = pre[now.x][now.y][now.status];
					//if(frame_id>=70&&frame_id<=120)cerr << tmp.x << " " << tmp.y <<' '<<tmp.status << endl;
					nxt[tmp.x][tmp.y][tmp.status] = now;
					now = tmp;
				}

				return;
			}
			if (u.flag == 0)
			{
				if (visited[u.x][u.y][u.dir])continue;
				visited[u.x][u.y][u.dir] = true;

				u.flag = 1;
				q.push(u);
			}
			else
			{
				for (int j = 0; j < 3; j++)
				{
					MyTuple tmp = MyTuple(u.x, u.y, u.dir);

					if (Boat::operate(tmp, j))
					{
						//cerr << "AAAAAAAAA" << endl;
						if (visited[tmp.x][tmp.y][tmp.status])continue;
						//cerr << "aaaaa" << endl;
						//cerr << tmp.x << ' ' << tmp.y << ' ' << tmp.status << endl;

						if (slow_or_not(tmp))//如果下一步减速了，则推入0
						{
							//if (frame_id >= 70 && frame_id <= 120&& tmp.y == 193) cerr << tmp.x << " " << tmp.y << " " << endl;
							//visited[tmp.x][tmp.y][tmp.status] = 1;
							q.push(Foursome(tmp.x, tmp.y, tmp.status, 0));
							pre[tmp.x][tmp.y][tmp.status] = MyTuple(u.x, u.y, u.dir);
						}
						else
						{
							visited[tmp.x][tmp.y][tmp.status] = true;
							pre[tmp.x][tmp.y][tmp.status] = MyTuple(u.x, u.y, u.dir);
							q.push(Foursome(tmp.x, tmp.y, tmp.status, 1));
						}
					}
				}
			}
		}
		step++;
	}
	//cerr << "out" << endl;
}


void Boat::find_road2() {	//启发式搜索，降低复杂度
	if (x == target_x && y == target_y) {
		return;
	}
	// def of dis, vis
	bool vis[200][200][4] = { false };
	int dis[200][200][4];
	memset(dis, 0x3f, sizeof dis);
	priority_queue<BoatRout> q;
	MyTuple begin = MyTuple(x, y, dir);
	dis[begin.x][begin.y][begin.status] = 0;
	BoatRout st;
	if (aim_berth != -1) {
		st = BoatRout(x, y, dir, 0, berth_dis[x][y][aim_berth]);
		q.push(st);
		while (q.size()) {
			BoatRout tp = q.top(); q.pop();
			if (tp.x == target_x && tp.y == target_y) {
				MyTuple now = MyTuple(tp.x, tp.y, tp.dir), tmp = MyTuple(0, 0, 0);
				while (tmp.x != x || tmp.y != y || tmp.status != dir)
				{
					tmp = pre[now.x][now.y][now.status];
					//if(frame_id>=70&&frame_id<=120)cerr << tmp.x << " " << tmp.y <<' '<<tmp.status << endl;
					nxt[tmp.x][tmp.y][tmp.status] = now;
					now = tmp;
				}
				return;
			}
			if (vis[tp.x][tp.y][tp.dir]) continue;
			vis[tp.x][tp.y][tp.dir] = true;
			MyTuple copy = MyTuple(tp.x, tp.y, tp.dir);
			for (int i : operation[rand() % 6]) {
				//for (int i = 0; i < 3; i++) {
				MyTuple tmp = copy;
				if (operate(tmp, i)) {
					int len = dis[copy.x][copy.y][copy.status] + (slow_or_not(tmp) ? 2 : 1);
					if (dis[tmp.x][tmp.y][tmp.status] > len) {
						dis[tmp.x][tmp.y][tmp.status] = len;
						pre[tmp.x][tmp.y][tmp.status] = MyTuple(tp.x, tp.y, tp.dir);
						BoatRout nw = BoatRout(tmp.x, tmp.y, tmp.status, len, berth_dis[tmp.x][tmp.y][aim_berth]);
						q.push(nw);
					}
				}
			}
		}
	}
	else {
		st = BoatRout(x, y, dir, 0, berth_dis[x][y][aim_delivery]);
		q.push(st);
		while (q.size()) {
			BoatRout tp = q.top(); q.pop();
			if (tp.x == target_x && tp.y == target_y) {
				MyTuple now = MyTuple(tp.x, tp.y, tp.dir), tmp = MyTuple(0, 0, 0);
				while (tmp.x != x || tmp.y != y || tmp.status != dir)
				{
					tmp = pre[now.x][now.y][now.status];
					//if(frame_id>=70&&frame_id<=120)cerr << tmp.x << " " << tmp.y <<' '<<tmp.status << endl;
					nxt[tmp.x][tmp.y][tmp.status] = now;
					now = tmp;
				}
				return;
			}
			if (vis[tp.x][tp.y][tp.dir]) continue;
			vis[tp.x][tp.y][tp.dir] = true;
			MyTuple copy = MyTuple(tp.x, tp.y, tp.dir);
			for (int i : operation[rand() % 6]) {
				//for (int i = 0; i < 3; i++) {
				MyTuple tmp = copy;
				if (operate(tmp, i)) {
					int len = dis[copy.x][copy.y][copy.status] + (slow_or_not(tmp) ? 2 : 1);
					if (dis[tmp.x][tmp.y][tmp.status] > len) {
						dis[tmp.x][tmp.y][tmp.status] = len;
						pre[tmp.x][tmp.y][tmp.status] = MyTuple(tp.x, tp.y, tp.dir);
						BoatRout nw = BoatRout(tmp.x, tmp.y, tmp.status, len, berth_dis[tmp.x][tmp.y][aim_delivery]);
						q.push(nw);
					}
				}
			}
		}
	}
}

bool Boat::two_boat_clash(MyTuple a, MyTuple b)
{
	unordered_map<int,int>mp;
	if (a.status == 2) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (a.x - j) * 1000 + a.y + i;
				mp[tp] += 1;
			}
		}
	}
	else if (a.status == 3) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (a.x + j) * 1000 + a.y - i;
				mp[tp] += 1;
			}
		}
	}
	else if (a.status == 1) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (a.x - i) * 1000 + a.y - j;
				mp[tp] += 1;
			}
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (a.x +i) * 1000 + a.y + j;
				mp[tp] += 1;
			}
		}
	}
	/////////////////////////////////////////////////
	if (b.status == 2) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (b.x - j) * 1000 + b.y + i;
				if (mp[tp] == 1)
				{
					if (!slow_or_not(make_pair(tp / 1000, tp % 1000)))return true;
				}
			}
		}
	}
	else if (b.status == 3) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (b.x + j) * 1000 + b.y - i;
				if (mp[tp] == 1)
				{
					if (!slow_or_not(make_pair(tp / 1000, tp % 1000)))return true;
				}
			}
		}
	}
	else if (b.status == 1) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (b.x - i) * 1000 + b.y - j;
				if (mp[tp] == 1)
				{
					if (!slow_or_not(make_pair(tp / 1000, tp % 1000)))return true;
				};
			}
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int tp = (b.x + i) * 1000 + b.y + j;
				if (mp[tp] == 1)
				{
					if (!slow_or_not(make_pair(tp / 1000, tp % 1000)))return true;
				}
			}
		}
	}
	return false;

}

void Boat::clash_solve(int op , MyTuple boat_a)
{   
	for (int i = boat_id + 1; i < boat_num; i++)
	{
		MyTuple boat_b = MyTuple(boat[i].x, boat[i].y, boat[i].dir);
		if (Boat::two_boat_clash(boat_a,boat_b))
		{
			string tmp = "dept " + to_string(boat_id);
			boat_option.push_back(tmp);
			dept_flag = true;
			return;
		}
	}
	if (op <= 1) {
		string tmp = "rot " + to_string(boat_id) + " " + to_string(op);
		boat_option.push_back(tmp);
		//cout << "rot " << boat_id << " " << j << endl;

	}
	else {
		string tmp = "ship " + to_string(boat_id);
		boat_option.push_back(tmp);
		//cerr << frame_id << " " << tmp << endl;
		//cout << "ship " << boat_id << endl;
	}

}


bool Boat::operate(MyTuple& t, int op) {	//给定t状态，做出op操作之后的状态，引用传递，所以t直接改变
	MyTuple tmp;
	if (op == 2) {
		tmp = MyTuple(t.x + fx[t.status], t.y + fy[t.status], t.status);
	}
	else if (op == 0) {
		tmp = MyTuple(t.x + rot_0x[t.status], t.y + rot_0y[t.status], rot_0dir[t.status]);
	}
	else {
		tmp = MyTuple(t.x + rot_1x[t.status], t.y + rot_1y[t.status], rot_1dir[t.status]);
	}
	//if(frame_id<3)cerr << tmp.x << ' ' << tmp.y << ' ' << tmp.status << endl;
	if (check_valid(tmp))
	{
		t = tmp;
		//if (frame_id < 3)cerr << "TURE" << endl;
		return true;
	}
	else
	{
		//if (frame_id < 3)cerr << "FALSE" << endl;
		return false;
	}
}

bool Boat::check_valid(const MyTuple& t) {
	int x = t.x, y = t.y, dir = t.status;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if ((dir == 2 && !sea_check_valid(x - j, y + i)) ||
				(dir == 3 && !sea_check_valid(x + j, y - i)) ||
				(dir == 1 && !sea_check_valid(x - i, y - j)) ||
				(dir == 0 && !sea_check_valid(x + i, y + j))) {
				return false;
			}
		}
	}
	return true;
}

void Boat::choose_berth()
{
	double max_num = .0;
	int target_berth = 0;
	for (int i = 0; i < berth_num; i++)	//挑选货物最多的泊位
	{
		if (berth_dis[x][y][i] == 0) {
			if (berth[i].left_num != 0) {
				target_berth = i;
				break;
			}
			else
				continue;
		}
		// here is the policy that can be changed
		double tmp = pow(berth[i].left_num * 1.0, 2) / pow(1.0 * berth_dis[x][y][i], 1);
		if (tmp > max_num)
		{
			max_num = tmp;
			target_berth = i;
		}
	}
	target_x = berth[target_berth].x;
	target_y = berth[target_berth].y;
	aim_berth = target_berth;
	aim_delivery = -1;
	if (goods_num == boat_capacity)
	{
		int min_dis = 300000, target_delivery = 0;
		for (int i = 0; i < delivery_num; i++)
		{
			if (delivery_dis[x][y][i] < min_dis)
			{
				target_delivery = i;
				min_dis = delivery_dis[x][y][i];
			}
		}
		target_x = delivery_point[target_delivery].first;
		target_y = delivery_point[target_delivery].second;
		aim_berth = -1;
		aim_delivery = target_delivery;
	}
}

int Boat::GetId() {
	return boat_id;
}

int Boat::cal_manhattan(MyTuple k) {
	return Manhattan(make_pair(k.x, k.y), make_pair(target_x, target_y));
}
