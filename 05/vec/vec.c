#include "vec.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Vec {
    double* data;
    size_t len;
    size_t cap;
};

static int vec_grow(Vec* v) {
    double* tmp = realloc(v->data, v->cap * 2 * sizeof *v->data);
    if (!tmp) {
        return -1; 
    }
    else { 
        v->data = tmp; 
        v->cap *= 2;
        return 0;
    }
}
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
    if (!v) return;
    
    free(v->data);
    free(v);
}

int vec_push(Vec* v, double x) {
    if (v->len == v->cap) {
        assert(vec_grow(v) == 0);
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

void vec_insert(Vec* v, size_t i, double x) {
    if (i > v->len) {
        return;
    } else if (i == v->len) {
        vec_push(v, x);
        return;
    }

    // handle growing first
    if (v->len == v->cap) {
        assert(vec_grow(v) == 0);
    }

    memmove(v->data + i + 1, v->data + i, (v->len - i) * sizeof *v->data);
    v->data[i] = x;
    v->len += 1;
    return;
}

void vec_remove(Vec* v, size_t i) {
    if (i >= v->len) return;
    if (i == v->len - 1) { vec_pop(v); return; }
    
    memmove(v->data + i, v->data + i + 1, (v->len - i - 1) * sizeof *v->data);
    v->len -= 1;
    return;
}
