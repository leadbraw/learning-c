#include <stdio.h>

// reads lines from console until EOF (ctrl+D in terminal) or newline, then echoes it back.
int main(void) {
	char line[128];
	int n = 1;
	while (fgets(line, sizeof line, stdin) != NULL) {
		printf("line %d: %s", n, line);
		n++;
	}
	return 0;
}
