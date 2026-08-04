#include <assert.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    float x, y;
} Vector2;

Vector2 v2_add(Vector2 a, Vector2 b) {
    Vector2 result = { a.x + b.x, a.y + b.y };
    return result;
}

float v2_len(Vector2 v) {
    return sqrtf((v.x * v.x) + (v.y * v.y));
}

bool v2_equal(Vector2 a, Vector2 b) {
    return a.x == b.x && a.y == b.y;
}

int main(void) {
    Vector2 v1 = { .x = 5, .y = 5 };
    Vector2 v2 = { .x = 1, .y = 1 };
    Vector2 v3 = { .x = 5, .y = 10 };

    assert(v2_equal(v2_add(v1, v2), (Vector2){6, 6}));
    assert(v2_equal(v2_add(v2, v3), (Vector2){6, 11}));
    assert(v2_equal(v2_add(v1, v3), (Vector2){10, 15}));

    assert(v2_len(v1) == (sqrtf(50)));
    assert(v2_len(v2) == (sqrtf(2)));
    assert(v2_len(v3) == (sqrtf(125)));
    return 0;
}
