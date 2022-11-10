#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;


//	https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mouse_event

void menu();
void doubleclick();
void click();
void openfile();
void newprogram();
void readprogram(string filename);
void emulate_keyboard(char _char);
void generate_output(string file_name);

int delay = 1500;
int typing_delay = 60;
int caps_lock = 0;

int main() {
	menu();
	return 0;	
}

void menu() {
	int d;
	string s;
	do {
		system("CLS");
		cout << "Specify action:\n0 exit\n1 write new program\n2 use saved program";
		cout << endl;
		cin >> d;
		switch (d) {
		case 1:
			newprogram();
			break;
		case 2:
			cout << "Specify program name: ";
			cin >> s;
			readprogram(s);
		default:
			break;
		}
	} while (d != 0);
}

void doubleclick() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void click() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void openfile() {

}

void newprogram() {
	POINT xypos;
	int d = 0;
	string name;
	ofstream file;
	cout << "Specify program name: ";
	cin >> name;
	file.open((".\\mouse_programs\\" + name + ".txt").c_str());
	do {
		system("CLS");
		if (d != 0) cout << "Last action: " << d << endl;
		cout << "Specify action:\n0 end\n1 go to current position\n2 click\n3 double click\n4 emulate keystrokes";
		cout << endl;
		cin >> d;
		switch (d) {
		case 1:
			GetCursorPos(&xypos);
			file << 1 << endl << xypos.x << endl << xypos.y << endl;
			break;
		case 2:
			file << 2 << endl;
			break;
		case 3:
			file << 3 << endl;
			break;
		case 4:
			generate_output(name);
		default:
			break;
		}
	} while (d != 0);
	file.close();
}

void readprogram(string filename) {
	POINT xypos;
	int d, x, y, i;
	char _char;
	string s;
	ifstream file;
	file.open((".\\mouse_programs\\" + filename + ".txt").c_str());
	while (file.good()) {
		file >> d;
		switch (d) {
		case 1:
			file >> x;
			file >> y;
			SetCursorPos(x, y);
			break;
		case 2:
			click();
			break;
		case 3:
			doubleclick();
			break;
		case 4:
			file >> x;
			if (x != 0) {
				for (i = 0; i < x; i++) {
					file >> _char;
					y = _char;
					emulate_keyboard(y - 32);
					Sleep(typing_delay);
				}
			}
			else emulate_keyboard(32);
			break;
		default:
			break;
		}
		Sleep(delay);
	}
	file.close();
}

void emulate_keyboard(char _char) {
	// This structure will be used to create the keyboard
	// input event.
	INPUT ip;

	// Pause for 5 seconds.
	Sleep(typing_delay);

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "A" key
	//ip.ki.wVk = 0x41; // virtual-key code for the "a" key
	ip.ki.wVk = _char;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));

	// Exit normally
}

void generate_output(string file_name) {
	ofstream file;
	file.open((".\\mouse_programs\\" + file_name + ".txt").c_str(),ios::app);
	int d, dec, i;
	string s;
	char buff;
	do {
		//	4 - operator for output
		//	string length
		file << 4 << endl;

		system("CLS");
		cout << "What do you want to emulate:\n1 string\n2 space\n";
		cin >> dec;
		switch (dec) {
		case 1:
			system("CLS");
			cout << "Enter input(lower case): ";
			cin >> s;

			//d = s.length();
			file << s.length() << endl;
			for (i = 0; i < s.length(); i++) {
				buff = s[i];
				file << buff << endl;
			}
			break;
		case 2:
			file << 0 << endl << 32 << endl;
			break;
		default:
			break;
		}
		
		system("CLS");
		cout << "Do you want to continue emulating key strokes?\n0 no\n1 yes\n";
		cin >> d;
		cin.clear();
	} while (d == 1);
	file.close();
}
