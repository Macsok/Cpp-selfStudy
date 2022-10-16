#include <iostream>
#include <cmath>
using namespace std;


//					ULAM SPIRAL


int prime(int n);
int turn(int dir);

int main() {
	int xx = 0;
	while (xx % 2 == 0) {
		cout << "Side length: ";
		cin >> xx;
	}

	int t[xx][xx];
	int x = xx / 2, y = x;
	int i, j;
	int direction = 0;	// 0 - right, 1 - up, 2 - left, 3 - down
	int step_length = 1, step = 0;

	for (i = 1; i <= xx * xx; ) {
		for (j = 0; j < step_length; j++) {
			t[y][x] = i;
			switch (direction) {
			case 0:
				x++;
				break;
			case 1:
				y--;
				break;
			case 2:
				x--;
				break;
			case 3:
				y++;
				break;
			default:
				break;
			}
			i++;
		}
		direction = turn(direction);
		step++;
		if (step == 2) {
			step_length++;
			step = 0;
		}
	}
	//		Display
	for (i = 0; i < xx; i++) {
		for (j = 0; j < xx; j++) {
			if (prime(t[i][j])) cout << t[i][j] << "\t";
			else cout << " " << "\t";
		}
		cout << "\n\n\n\n";
	}
	return 0;
}

int turn(int dir) {
	if (dir == 0) return 1;
	else if (dir == 1) return 2;
	else if (dir == 2) return 3;
	else return 0;
}

int prime(int n) {
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) return 0;
	}
	return 1;
}