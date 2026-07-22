#include <stdio.h>

// prints out the size of the int types in bytes.
int main(void) {
	printf("/==| Integer type sizes (bytes) |==/\n");
	printf("char: %zu\n", sizeof(char));
	printf("short: %zu\n", sizeof(short));
	printf("int: %zu\n", sizeof(int));
	printf("long: %zu\n", sizeof(long));
	printf("long long: %zu\n", sizeof(long long));

	return 0;
}
