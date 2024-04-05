#include "boat.h"
using namespace std;

int Boat::boat_num = 0;
const int fx[4] = { 0, 0, -1, 1 };
const int fy[4] = { 1, -1, 0, 0 };
const int rot_0x[4] = { 0,0,-2,2 };
const int rot_0y[4] = { 2,-2,0,0 };
const int rot_1x[4] = { 1,-1,-1,1 };
const int rot_1y[4] = { 1,-1,1,-1 };
const int rot_0dir[4] = { 3,2,0,1 };
const int rot_1dir[4] = { 2,3,1,0 };
bool Boat::boat_loc[200][200] = { false }; // all the origin loc is false

// Before create one boat, check if it's valid
Boat::Boat(int id, int X, int Y, direction Dir, int Status, int Num_goods) :
	boat_id(boat_num), x(X), y(Y), dir(Dir), status(Status), goods_num(Num_goods)
{
	boat_num++;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			boat_loc[i][j] = true;
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
	if (boat_loc[x][y]) // there is a ship
		return tmp == '~' || tmp == 'S' || tmp == 'c' || tmp == 'B' || tmp == 'K' || tmp == 'T';
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

int Boat::cal_manhattan(MyTuple k) {
	return Manhattan(make_pair(k.x, k.y), make_pair(target_x, target_y));
}

void Boat::find_road2() {
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
	BoatRout st = BoatRout(x, y, dir, 0, Manhattan(make_pair(x, y), make_pair(target_x, target_y)));
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
		for (int i = 0; i < 3; i++) {
			MyTuple tmp = copy;
			if (operate(tmp, i)) {
				int len = dis[copy.x][copy.y][copy.status] + (slow_or_not(tmp) ? 2 : 1);
				if (dis[tmp.x][tmp.y][tmp.status] > len) {
					dis[tmp.x][tmp.y][tmp.status] = len;
					pre[tmp.x][tmp.y][tmp.status] = MyTuple(tp.x, tp.y, tp.dir);
					BoatRout nw = BoatRout(tmp.x, tmp.y, tmp.status, len, cal_manhattan(tmp));
					q.push(nw);
				}
			}
		}
	}
}

<<<<<<< Updated upstream
#if(0)

bool Boat::Forward(MyTuple& k) {
	int& x = k.x, & y = k.y, & dir = k.status;
	if (dir == north) { //north
		int _x = x - 3, _y = y + 1;
		if (!sea_check_valid(_x, y) || !sea_check_valid(_x, _y))
			return false;
		boat_loc[x][y] = boat_loc[x][_y] = false;
		boat_loc[_x][y] = boat_loc[_x][_y] = true;
		x--;
	}
	else if (dir == south) {//south
		int _x = x + 3, _y = y - 1;
		if (!sea_check_valid(_x, _y) || !sea_check_valid(_x, y))
			return false;
		boat_loc[x][y] = boat_loc[x][_y] = false;
		boat_loc[_x][y] = boat_loc[_x][_y] = true;
		x++;
	}
	else if (dir == west) {//west
		int _x = x - 1, _y = y - 3;
		if (!sea_check_valid(_x, _y) || !sea_check_valid(_x, y))
			return false;
		boat_loc[x][y] = boat_loc[x][_y] = false;
		boat_loc[_x][y] = boat_loc[_x][_y] = true;
		y--;
	}
	else {//east
		int _x = x + 1, _y = y + 3;
		if (!sea_check_valid(_x, _y) || !sea_check_valid(_x, y))
			return false;
		boat_loc[x][y] = boat_loc[x][_y] = false;
		boat_loc[_x][y] = boat_loc[_x][_y] = true;
		y++;
	}
	return true;
}
bool Boat::AntiClock(MyTuple& k) {
	int& x = k.x, & y = k.y, & dir = k.status;
	int kx = x, ky = y;
	int kdir = dir;
	x += projection_x[dir];
	y += projection_y[dir];
	dir = (dir + 4 - 1) % 4;
	x -= projection_x[dir];
	y -= projection_y[dir];

	if (dir == west) {
		if (!sea_check_valid(x, y - 2) || !sea_check_valid(x - 1, y - 2)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x][y - 2] = boat_loc[x - 1][y - 2] = true;
		boat_loc[kx][ky + 1] = boat_loc[kx][ky] = false;
	}
	else if (dir == north) {
		if (!sea_check_valid(x - 2, y) || !sea_check_valid(x - 2, y + 1)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x - 2][y] = boat_loc[x - 2][y + 1] = true;
		boat_loc[kx][ky] = boat_loc[kx + 1][ky] = false;
	}
	else if (dir == east) {
		if (!sea_check_valid(x, y + 2) || !sea_check_valid(x + 1, y + 2)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x][y + 2] = boat_loc[x + 1][y + 2] = true;
		boat_loc[kx][ky - 1] = boat_loc[kx][ky] = false;
	}
	else {
		if (!sea_check_valid(x + 2, y) || !sea_check_valid(x + 2, y - 1)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x + 2][y] = boat_loc[x + 2][y - 1] = true;
		boat_loc[kx][ky] = boat_loc[kx - 1][ky] = false;
	}
	return true;
}

bool Boat::Clockwise(MyTuple& k) {
	int& x = k.x, & y = k.y, & dir = k.status;
	int kx = x, ky = y;
	int kdir = dir;

	x += projection_x[dir];
	y += projection_y[dir];
	dir = (dir + 1) % 4;

	if (dir == west) {
		if (!sea_check_valid(x, y - 2) || !sea_check_valid(x - 1, y - 2)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x][y - 2] = boat_loc[x - 1][y - 2] = true;
		boat_loc[kx][ky - 1] = boat_loc[kx][ky] = false;
	}
	else if (dir == north) {
		if (!sea_check_valid(x - 2, y) || !sea_check_valid(x - 2, y + 1)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x - 2][y] = boat_loc[x - 2][y + 1] = true;
		boat_loc[kx][ky] = boat_loc[kx - 1][ky] = false;
	}
	else if (dir == east) {
		if (!sea_check_valid(x, y + 2) || !sea_check_valid(x + 1, y + 2)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x][y + 2] = boat_loc[x + 1][y + 2] = true;
		boat_loc[kx][ky + 1] = boat_loc[kx][ky] = false;
	}
	else {
		if (!sea_check_valid(x + 2, y) || !sea_check_valid(x + 2, y - 1)) {
			x = kx, y = ky;
			dir = kdir;
			return false;
		}
		boat_loc[x + 2][y] = boat_loc[x + 2][y - 1] = true;
		boat_loc[kx][ky] = boat_loc[kx + 1][ky] = false;
	}

	return true;
}
#endif

bool Boat::operate(MyTuple& t, int op) {
=======
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
		//cout << "ship " << boat_id << endl;
	}

}

bool Boat::operate(MyTuple& t, int op) {	//给定t状态，做出op操作之后的状态，引用传递，所以t直接改变
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
<<<<<<< Updated upstream
void Boat::Boat_control()
=======
/*
* need to change!!!
* give more weights to the distance you take.
* update: we can predict more steps.
=======
/*
* take more steps into account?
>>>>>>> Stashed changes
*/
void Boat::choose_berth()
>>>>>>> Stashed changes
{
<<<<<<< Updated upstream
	//cerr << robot_num << endl;
	if (status == 1)return;
	//cerr << frame_id << endl;
	//cerr << nxt[x][y][dir].x << ' ' << nxt[x][y][dir].y << ' ' << nxt[x][y][dir].status << endl;
	if (status == 2)
	{
		if (berth[0].num > 0 && goods_num < boat_capacity)
		{
			int add = min(berth[0].loading_speed, min(boat_capacity - goods_num, berth[0].num));
			goods_num += add;
			berth[0].num -= add;
		}
		else
		{
			target_x = delivery_point[0].first;
			target_y = delivery_point[0].second;
			//left_time = berth[aim_berth].transport_time;
			leave_flag = true;
			cout << "dept " << boat_id << endl;
		}
		return;
	}
	if (target_x == -1)
	{
		target_x = berth[0].x;
		target_y = berth[0].y;
		find_road2();
	}
	else
	{
		if (target_x == x && target_y == y)
		{
			if (x == berth[0].x && y == berth[0].y)
			{
				cout << "berth 0\n";
			}
			else
			{
				target_x = berth[0].x; target_y = berth[0].y;
				find_road2();
			}
			return;
		}
		if (target_x == delivery_point[0].first && leave_flag == true)
		{
			find_road2();
			leave_flag = false;
			return;
		}
		//cerr << frame_id << endl;
		//cerr << x << ' ' << y << ' ' << status << endl;

		for (int j = 0; j <= 2; j++)
		{
			//cerr << "see see\n";
			//cerr << "j = " << j << endl;
			MyTuple tmp = MyTuple(x, y, dir);
			//if(frame_id<10)cerr << nxt[x][y][dir].x << nxt[x][y][dir].y << nxt[x][y][dir].status << endl;
			if (operate(tmp, j)) {
				//cerr << 111111 << endl;
				//if (frame_id < 10)cerr << j<<' '<<tmp.x << ' ' << tmp.y << ' ' << tmp.status << endl;
				if (tmp == nxt[x][y][dir]) {
					if (j <= 1) {
						cout << "rot 0 " << j << endl;
						//cerr << "rot 0 " << j << endl;

					}
					else {
						cout << "ship 0\n";
						//cerr << "ship 0\n";
					}
					return;
				}
			}
=======
	double max_num = .0;
	target_berth = 0;
	for (int i = 0; i < berth_num; i++)	//挑选货物最多的泊位
	{
		// here is the policy that can be changed
#if(1)
		if (berth_dis[x][y][i] == 0) {
			if (berth[i].left_num != 0) {
				target_berth = i;
				break;
			}
			else
				continue;
		}
		double tmp = berth[i].left_num * 1.0 / berth_dis[x][y][i];
#else
		double tmp = berth[i].left_num * 1.0;
#endif
		if (tmp > max_num)
		{
			max_num = tmp;
			target_berth = i;
>>>>>>> Stashed changes
		}
	}

}

int Boat::GetId() {
	return boat_id;
}