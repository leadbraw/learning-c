#include <assert.h>
#include <stdlib.h>

// writing some bugs to get used to what the warnings look like in gcc and/or valgrind.
int main(void) {
    /* use after free */
    int* arr1 = malloc(5 * sizeof *arr1);
    assert(arr1 != NULL);
    arr1[0] = 2666;
    free(arr1);
    arr1[5] = 80;

    /* off by one */
    int* arr2 = malloc(5 * sizeof *arr2);
    assert(arr2 != NULL);
    arr2[4] = 2666; // okay
    arr2[5] = 2667; // not okay
    free(arr2);
    return 0;
}
