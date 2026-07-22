#include <stdio.h>

int main(void) {
	char line[128];
	int n = 1;
	while (fgets(line, sizeof line, stdin) != NULL) {
		printf("line %d: %s", n, line);
		n++;
	}
	return 0;
}
