#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(void) {
    int* ints = malloc(100 * sizeof *ints);
    assert(ints != NULL);
    for (int i = 0; i < 100; i++) {
        ints[i] = i + 1; // 100 ints 1-100
        printf("%d,", ints[i]);
    }
    printf("\n");
    free(ints); // added this line after doing valgrind --leak-check=full ./mass_malloc
    return 0;
}
