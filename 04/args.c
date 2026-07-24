#include <stdio.h>

int main (int argc, char* argv[]) {
    // prints all args (reverse order) (except program name) and their length (w/o strlen)
    if (argc < 2) return 0;

    for (int i = argc - 1; i > 0; i--) {
        printf("Arg %d: %s\n", i + 1, argv[i]);

        char* l = argv[i];
        while (*l) {
            l++;
        }
        printf("Arg %d length: %zu\n", i + 1, l - argv[i]);
    }

    return 0;
}
