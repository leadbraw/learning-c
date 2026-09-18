#include <stdio.h>

#define MIN(a, b) (((b) < (a)) ? (b) : (a))
#define MAX(a, b) (((b) > (a)) ? (b) : (a))


int main(void) {
    printf("4, 5 min: %d\n", MIN(4, 5));
    printf("11, -20 min: %d\n", MIN(11, -20));
    printf("1, 3 max: %d\n", MAX(1, 3));
    printf("-1, -5 max: %d\n", MAX(-1, -5));

    /* was gonna show off the side effect if you pass in like x++ to a macro but nothing
    gets past the compiler */
    return 0;
}
