#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;


//	ANSI ESCAPE CODES


const int L = 50;
int stan[2][L][L];

void init(int _c) {
	for (int y = 0; y < L; y++)
		for (int x = 0; x < L; x++) {
			if (rand() % 7 == 1)
				stan[_c][y][x] = 1;
			else stan[_c][y][x] = 0;
		}
}

//	Refresh every pixel
void animate(int _c) {
	for (int y = 0; y < L; y++)
		for (int x = 0; x < L; x++) {
			cout << "\x1b[" << x + 1 << ";" << y + 1 << "H";
			if (stan[_c][y][x] == 1) cout << "\x1b[42m " << "\x1b[0m";
			else cout << " ";
			//else cout << "\x1b[100m " << "\x1b[0m";
		}
	//cout << "\x1b[" << L << ";" << L << "H";
}

//	Clear screen and display new one
void display(int _c) {
	system("CLS");
	for (int y = 0; y < L; y++)
		for (int x = 0; x < L; x++) {
			cout << "\x1b[" << y + 1 << ";" << x + 1 << "H";
			if (stan[_c][y][x] == 1) cout << "\x1b[42m " << "\x1b[0m";
			//else cout << "\x1b[100m " << "\x1b[0m";
		}
	//cout << "\x1b[" << L << ";" << L << "H";
}

int neighbours(int y, int x, int _c) {
	int xleft, xright, yup, ydown;
	// Warunki cykliczne
	if (y == 0) yup = L - 1;
		else yup = y + 1;
	if (y == L - 1) ydown = 0;
		else ydown = y - 1;
	if (x == 0) xleft = L - 1;
		else xleft = x - 1;
	if (x == L - 1) xright = 0;
		else xright = x + 1;
	return stan[_c][yup][x] + stan[_c][ydown][x] + stan[_c][y][xright] + stan[_c][y][xleft] +
		stan[_c][yup][xleft] + stan[_c][ydown][xleft] + stan[_c][yup][xright] + stan[_c][ydown][xright];
}

void gameoflife(int _c) {
	int n;
	for (int y = 0; y < L; y++)
		for (int x = 0; x < L; x++) {
			n = neighbours(y, x, _c);
			if (stan[_c][y][x] == 0 && n == 3) stan[1 - _c][y][x] = 1;
			else if (stan[_c][y][x] == 1 && (n == 2 || n == 3)) stan[1 - _c][y][x] = 1;
			else stan[1 - _c][y][x] = 0;
		}
}

int main() {
	srand(time(NULL));
	int c = 1;
	init(c);
	/*stan[1][9][15] = 1;
	stan[1][9][16] = 1;
	stan[1][9][17] = 1;*/
	system("CLS");
	for (int t = 0; t < 100; t++) {
		
		animate(c);
		//display(c);
		cout << "\x1b[" << L << ";" << L << "H";
		// Naprzemiennie 1, 0
		
		gameoflife(c);
		c = 1 - c;
		
		//Sleep(500);
	}
	return 0;
}