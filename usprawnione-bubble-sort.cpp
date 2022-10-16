#include  <iostream>
using namespace std;

int main() {
	int t[7], i, j;
	bool sorted = false;

	for(i = 0; i < 7; i++) {
		cout << "Podaj liczbe: ";
		cin >> t[i];
	}

	for(i = 0; i < 6; i++) {
		sorted = true;
			for(j = 0; j < (6-i); j++) {
			if(t[j] > t[j+1]) {
				swap(t[j], t[j+1]);
				sorted = false;
			}
		}
		if(sorted == true) break;
	}

	for(i = 0; i < 7; i++) {
		cout << t[i] << "\t";
	}
	return 0;
}	