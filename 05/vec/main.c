#include "vec.h"
#include <assert.h>
#include <stdio.h>

void printvec(Vec* v);

int main(void) {
    Vec* v = vec_new();
    for (int i = 1; i <= 1000000; i++) {
        vec_push(v, (double) i);
    }
    assert(vec_get(v, 50) == 51.00);
    assert(vec_get(v, 999999) == 1000000.00);
    assert(vec_get(v, 0) == 1.00);
    while (vec_len(v) > 0) {
        vec_pop(v);
    }
    vec_free(v);

    Vec* v2 = vec_new();
    for (int i = 1; i <= 8; i++) {
        vec_push(v2, (double) i);
    }
    printvec(v2);
    printf("\n");
    vec_insert(v2, 0, 100);
    printvec(v2);
    printf("\n");
    vec_insert(v2, 9, 101);
    printvec(v2);
    printf("\n");
    vec_remove(v2, 0);
    printvec(v2);
    printf("\n");
    vec_remove(v2, 8);
    printvec(v2);
    printf("\n");
    vec_free(v2);

    Vec *v3 = vec_new();
    for (int i = 0; i < 8; i++) {
        vec_push(v3, i);
    }
    vec_remove(v3, 3);
    vec_free(v3);
    return 0;
}

void printvec(Vec* v) {
    for (size_t i = 0; i < vec_len(v); i++) {
        printf("%f,", vec_get(v, i));
    }
}
