#include <stdio.h>

void swap(int* x, int* y);

int main(void) {
    int x = 2;
    int y = 3;
    printf("x, y (pre swap): %d, %d\n", x, y);
    swap(&x, &y);
    printf("x, y (post swap): %d, %d\n", x, y);
    return 0;
}

void swap(int* x, int* y) {
    // swaps values of two ints.
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
