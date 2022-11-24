#include <stdio.h>

//	Dane skladane na stosie (heap)
void cursedPrint(char* text) {
	char* ptr = text;
	while (*ptr) ptr++;
	ptr++;
	printf("%s\nbtw, I know your password, it's %s", text, ptr);
}


//	int - 32 bity, char - 8 bitow; rzutowanie bierze ostatnie 8 -> 2^8 = 256
int divBy256(int numb) {
	return !*((char*)(&numb));
}


int main() {
	char* example = "Some text to output";
	char* pass = "PASSWORD";
	cursedPrint(example);

	int n = 256;
	printf("%d", divBy256(n));
}