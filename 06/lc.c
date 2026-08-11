#include <stdio.h>

// wc -l
int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    FILE* f = fopen(argv[1], "r");
    if (!f) { perror("Error opening file"); return 1; }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof line, f)) {
        count++;
    }
    printf("line count: %d\n", count);
    return 0;
}
