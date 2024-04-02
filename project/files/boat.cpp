#include "boat.h"
using namespace std;

int Boat::boat_num = 0;
int Boat::projection_x[4] = { -1, 0, 1, 0 };
int Boat::projection_y[4] = { 0, 1, 0, -1 };
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
	if (dir == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!slow_or_not(make_pair(x - j, y + i)))
					return false;
			}
		}
	}
	else if (dir == 2) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!slow_or_not(make_pair(x + j, y - i)))
					return false;
			}
		}
	}
	else if (dir == 3) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!slow_or_not(make_pair(x - i, y - j)))
					return false;
			}
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!slow_or_not(make_pair(x + i, y + j)))
					return false;
			}
		}
	}
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
	if (x == target_x && y == target_y) return;
	memset(pre, 0, sizeof(pre));
	memset(nxt, 0, sizeof(nxt));
	memset(visited, false, sizeof(visited));
	visited[x][y][dir] = true;
	queue<Foursome>q;
	if (slow_or_not(MyTuple(x,y,dir)))//如果初始点包含主航道
	{
		q.push(Foursome(x, y, dir, 0));
	}
	else
	{
		q.push(Foursome(x, y, dir, 1));
	}
	bool found = false;
	int step = 0;
	while (!found && !q.empty())
	{
		int q_size = q.size();
		for (int i = 1; i <= q_size; i++)
		{
			Foursome u = Foursome(q.front().x,q.front().y,q.front().dir,q.front().flag);
			q.pop();
			if (u.x == target_x && u.y == target_y)
			{
				found = true;
				MyTuple now = MyTuple(u.x,u.y,u.dir), tmp = MyTuple(0, 0, 0);
				while (tmp.x != x || tmp.y != y || tmp.status != dir)
				{
					tmp = pre[now.x][now.y][now.status];
					nxt[tmp.x][tmp.y][tmp.status] = now;
					now = tmp;
				}
				break;
			}
			if (u.flag == 0)
			{
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
						if (slow_or_not(tmp))//如果下一步减速了，则推入0
						{
							q.push(Foursome(tmp.x, tmp.y, tmp.status, 0));
						}
						else
						{
							q.push(Foursome(tmp.x, tmp.y, tmp.status, 1));
						}
					}
				}
			}
		}
		step++;
	}
}

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


bool Boat::operate(MyTuple& t, int op) {
	if (op == 2) {
		if (!Forward(t))
			return false;
	}
	else if (op == 1) {
		if(!AntiClock(t))
			return false;
	}
	else {
		if (!Clockwise(t))
			return false;
	}
	return true;
}

bool Boat::check_valid(const MyTuple& t) {
	int x = t.x, y = t.y, dir = t.status;
	if (dir == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if(!sea_check_valid(x - j, y + i))
					return false;
			}
		}
	}
	else if (dir == 2) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!sea_check_valid(x + j, y - i))
					return false;
			}
		}
	}
	else if (dir == 3) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!sea_check_valid(x - i, y - j))
					return false;
			}
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!sea_check_valid(x + i, y + j))
					return false;
			}
		}
	}
	return true;
}

void Boat::Boat_control()
{

}

int Boat::GetId() {
	return boat_id;
}
