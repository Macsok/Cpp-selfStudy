#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

const int DIMENSION = 40;
const int LENGTH = 100;
const int SPEED = 0;
const int DENSITY = 50;		// bigger number => lower density

int yx[DIMENSION][DIMENSION] = {};
int mid = rand() % (DIMENSION - 10) + 6;
void generate_sky();
void animate(int n_times);
void place_collector();
void place_roof();

int main() {
	srand(time(0));
	//place_collector();
	place_roof();
	animate(LENGTH);
	return 0;
}

void generate_sky() {
	int x, y;
	for (x = DIMENSION - 1; x >= 0; x--) {
		if (yx[DIMENSION - 1][x] == 2)
			yx[DIMENSION - 1][x] = 0;
		if (yx[DIMENSION - 1][x] == 1)
			yx[DIMENSION - 1][x] = 2;
	}
	for (y = DIMENSION - 2; y >= 0; y--) {
		for (x = DIMENSION - 1; x >= 0; x--) {
			if (yx[y][x] == 1) {
				yx[y][x] = 0;
				if (yx[y + 1][x] == 7) {
					switch (rand() % 2) {
					case 0:
						yx[(DIMENSION / 2) + 2][mid + 5] = 1;
						break;
					case 1:
						yx[(DIMENSION / 2) + 2][mid - 5] = 1;
						break;
					default:
						break;
					}
				}
				else
					yx[y + 1][x] = 1;
			}
		}
	}
	for (x = DIMENSION - 1; x >= 0; x--) {
		if (rand() % DENSITY == 0) {
			yx[0][x] = 1;
			x = x - rand() % 3;
		}
	}
}

void animate(int n_times) {
	int i, y, x;
	for (i = 0; i < n_times; i++) {
		generate_sky();
		for (y = 0; y < DIMENSION; y++) {
			for (x = 0; x < DIMENSION; x++) {
				switch (yx[y][x]) {
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "o";
					break;
				case 2:
					cout << "_";
					break;
				case 3:
					cout << "-";
					break;
				case 4:
					cout << "|";
					break;
				case 5:
					cout << "\\";
					break;
				case 6:
					cout << "/";
					break;
				case 7:
					cout << "-";
					break;
				default:
					break;
				}
				cout << " ";
			}
			cout << "\n";
		}
		Sleep(SPEED);
		system("CLS");
	}
}

void place_collector() {
	int mid = rand() % (DIMENSION - 6) + 2;
	yx[DIMENSION - 1][mid] = 3;
	yx[DIMENSION - 1][mid - 1] = yx[DIMENSION - 1][mid + 1] = 4;
	yx[DIMENSION - 2][mid - 1] = yx[DIMENSION - 2][mid + 1] = 4;
	yx[DIMENSION - 3][mid - 1] = yx[DIMENSION - 3][mid + 1] = 4;
	yx[DIMENSION - 4][mid - 2] = 5;
	yx[DIMENSION - 4][mid + 2] = 6;
}

void place_roof() {
	yx[(DIMENSION / 2) + 1][mid - 4] = yx[(DIMENSION / 2) + 1][mid - 3] = yx[(DIMENSION / 2) + 1][mid + 3] = yx[(DIMENSION / 2) + 1][mid + 4] = 7;
	yx[DIMENSION / 2][mid - 2] = yx[DIMENSION / 2][mid - 1] = yx[DIMENSION / 2][mid] = yx[DIMENSION / 2][mid + 1] = yx[DIMENSION / 2][mid + 2] = 7;
}
