#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
using namespace std;

/*
	int a = 13;
	int *w = &a;		<- wskaznik wskazuje na & (adres a)

	cout << w;		adres wskaznika
	cout << *w;		wartosc wskazywanej zmienne (czyli a)

	float function(int &a);		& - ampersand (daj funkcji adres zmiennej)
	function(number)			przekazujemy zmienna, a funkcja dostaje jej adres przez uzycie ampersanda
*/

void generate_ceiling(int* tab, int length);
void form_spikes(int* tab_y0, int* tab_y1, int length);
void merge_ceiling(int* y0, int* y1, int* merged, int length);
void sky_anim(int* sky, int* spikes, int length);
void display(int* sky, int* ceiling, int length);

int main() {
	srand(time(0));
	int length = 30;
	int animation_length = 100;
	int anim_duration = 200;
	int animation_speed = 70;
	int gen_0[length] = {}, gen_1[length] = {};
	int ceiling[length * 2] = {}, sky[length * (length - 2)] = {};
	int i, j;

	generate_ceiling(gen_1, length);
	form_spikes(gen_0, gen_1, length);
	merge_ceiling(gen_0, gen_1, ceiling, length);

	for (i = 0; i < anim_duration; i++) {
		sky_anim(sky, gen_1, length);
		display(sky, ceiling, length);
		Sleep(animation_speed);
		system("CLS");
	}

	return 0;
}

void generate_ceiling(int* tab, int length) {
	int i, d;
	tab++;
	for (i = 1; i < length; i++) {
		d = rand() % 3 + 3;
		if (rand() % 2) {
			*tab = 1;
			tab += d;
			i += d;
		}
		else {
			tab += d;
			i += d;
		}
	}
}
//		\ <- 2		/ <- 3
void form_spikes(int* tab_y0, int* tab_y1, int length) {
	int i, d;
	tab_y1++;
	for (i = 1; i < length; i++) {
		if(*tab_y1) {
			*tab_y0 = 2;
			*tab_y1 = 2;
			tab_y0 += 2;
			*tab_y0 = 3;
			tab_y1 += 3;
			tab_y0++;
			i++;
		}
		else {
			tab_y0++;
			tab_y1++;
		}
	}
}

void merge_ceiling(int* y0, int* y1, int* merged, int length) {
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < length; j++) {
			if (i == 0) {
				*merged = *y0;
				merged++;
				y0++;
			}
			else {
				*merged = *y1;
				merged++;
				y1++;
			}
		}
	}
}
//		One frame of the animation			7 - dot
void sky_anim(int* sky, int* spikes, int length) {
	int i;
	sky = sky + length * (length - 2) - 1;
	for (i = 0; i < length; i++) {
		if (*sky == 7) *sky = 0;
		sky--;
	}

	for (i = 1; i < length * (length - 3); i++) {
		if (*sky == 7) {
			*sky = 0;
			sky += length;
			*sky = 7;
			sky -= length;
		}
		sky--;
	}

	for (i = 0; i < length; i++) {
		if (*spikes == 2) {
			if (rand() % 9 == 0) {
				*sky = 7;
			}
		}
		spikes++;
		sky++;
	}
}

void display(int* sky, int* ceiling, int length) {
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < length; j++) {
			if (*ceiling == 0) cout << " ";
			else if (*ceiling == 2) cout << "\\";
			else cout << "/";
			cout << "\t";
			ceiling++;
		}
		cout << "\n\n\n\n";
	}
	for (i = 0; i < length - 2; i++) {
		for (j = 0; j < length; j++) {
			if (*sky == 0) cout << " ";
			else cout << "o";
			cout << "\t";
			sky++;
		}
		cout << "\n\n\n\n";
	}
}