#include "boat.h"
using namespace std;

int Boat::boat_num = 0;
int Boat::projection_x[4] = { -1, 0, 1, 0 };
int Boat::projection_y[4] = { 0, 1, 0, -1 };

// first and foremost, init the boat loc!
void Boat::init_boat_loc() {
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			boat_loc[i][j] = false;
		}
	}
}

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

bool Boat::Forward() {
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
bool Boat::AntiClock() {
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

bool Boat::Clockwise() {
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

void Boat::Boat_control()
{

}

int Boat::GetId() {
	return boat_id;
}
