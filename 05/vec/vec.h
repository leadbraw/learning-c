#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct Vec Vec;

Vec *vec_new(void);
void vec_free(Vec* v);
int vec_push(Vec* v, double x);
double vec_get(const Vec* v, size_t i);
size_t vec_len(const Vec* v);
void vec_pop(Vec *v);

#endif
