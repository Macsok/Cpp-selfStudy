#include <iostream>
#include <Windows.h>
using namespace std;

//
//			N
//			|
//		W --+-- E
//		    |
//			S
//

int turn(int dir);
int on_wall(int x, int y, int length);
int move_x(int x, int dir);
int move_y(int y, int dir);

int main() {
	int xx = 5;
	int anim_length = 50;
	int anim_speed = 40;

	int t[xx][xx] = {};
	int buff_x, buff_y;
	int x = xx / 2, y = 0, i = 1, m, n;
	int direction = 3;		// 0 - WS		1 - SE		2 - NE		3 - NW		DEFAULT 3 (TURN ON WALL)
	for (i = 0; i < anim_length; i++) {
		t[y][x] = 2;

		//		NOTE T[Y][X]	Y-ROWS	X-COLUMNS

		buff_x = x;
		buff_y = y;
		if (on_wall(x, y, xx))  direction = turn(direction);
		x = move_x(x, direction);
		y = move_y(y, direction);
		t[y][x] = 1;

		//		Display

		for (m = 0; m < xx; m++) cout << "-------";
		cout << endl;

		for (m = 0; m < xx; m++) {
			cout << "| ";
			for (n = 0; n < xx; n++) {
				if (t[m][n])
					if (t[m][n] == 1) cout << "O";
					else cout << ".";
				else cout << " ";
				if (n != xx - 1) cout << "\t";
			}
			cout << " |";
			if (m != xx - 1) cout << "\n\n\n\n";
		}

		cout << endl;
		for (m = 0; m < xx; m++) cout << "-------";

		//		------

		t[buff_y][buff_x] = 0;
		Sleep(anim_speed);
		//cout << i << "-----------\n";
		system("CLS");		// Clear console
	}

	return 0;
}

int turn(int dir) {
	if (dir == 0) return 1;
	else if (dir == 1) return 2;
	else if (dir == 2) return 3;
	else return 0;
}

int on_wall(int x, int y, int length) {
	if (y == 0) return 1;
	else if (x == 0) return 1;
	else if (y == length - 1) return 1;
	else if (x == length - 1) return 1;
	else return 0;
}

int move_x(int x, int dir) {
	switch (dir) {
	case 0:
		return x - 1;
	case 1:
		return x + 1;
	case 2:
		return x + 1;
	case 3:
		return x - 1;
	default:
		break;
	}
	return 0;
}

int move_y(int y, int dir) {
	switch (dir) {
	case 0:
		return y + 1;
	case 1:
		return y + 1;
	case 2:
		return y - 1;
	case 3:
		return y - 1;
	default:
		break;
	}
	return 0;
}