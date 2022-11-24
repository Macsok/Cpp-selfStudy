#define MAX(a, b) ((a > b) ? (a) : (b))

#define TO_LOWER(x) (((x) < 0x5b && (x) > 0x40) ? (x) + 0x20 : (x))

//	int is as default
n = 100;

main() {
	int x = 2, y = 3;
	printf("%d", n + MAX(x + 3, y + 1));
	printf("%c", TO_LOWER('S'));
	return 0;
}