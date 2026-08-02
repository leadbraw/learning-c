#include "vec.h"
#include <assert.h>

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
    return 0;
}
