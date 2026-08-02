#include "vec.h"
#include <stdlib.h>
#include <assert.h>

struct Vec {
    double* data;
    size_t len;
    size_t cap;
};

Vec* vec_new(void) {
    Vec* v = malloc(sizeof(*v));
    if (!v) return NULL;
    v->data = malloc(8 * sizeof *v->data);
    if (!v->data) {
        free(v);
        return NULL;
    }
    v->len = 0;
    v->cap = 8;
    return v;
}

void vec_free(Vec* v) {
    free(v->data);
    free(v);
}

int vec_push(Vec* v, double x) {
    if (v->len == v->cap) {
        double* tmp = realloc(v->data, v->cap * 2 * sizeof *v->data);
        if (!tmp) {
            return -1; 
        }
        else { 
            v->data = tmp; 
            v->cap *= 2;
        }
    }
    v->data[v->len++] = x;
    return 0;
}

double vec_get(const Vec* v, size_t i) {
    assert(i < v->len);
    return v->data[i];
}

size_t vec_len(const Vec* v) {
    return v->len;
}

void vec_pop(Vec *v) {
    if (v->len == 0) return;
    v->len -= 1; // we'll just overwrite it on the next push
}
