#include <stdio.h>

size_t my_strlen(const char* s);

int main(void) {
    char s1[] = ""; // 0
    char s2[] = "Hello, World!"; // 13
    char s3[] = "Okay Okay"; // 9
    char s4[] = "In the false dawn everything is dreamlike and unreal"; // 52
    char s5[] = "Read this\0, Not this"; // 9

    printf("s1 len (expected: 0): %zu\n", my_strlen(s1));
    printf("s2 len (expected: 13): %zu\n", my_strlen(s2));
    printf("s3 len (expected: 9): %zu\n", my_strlen(s3));
    printf("s4 len (expected: 52): %zu\n", my_strlen(s4));
    printf("s5 len (expected: 9): %zu\n", my_strlen(s5));
}

size_t my_strlen(const char* s) {
    const char* c = s;
    while (*c) {
        c++;
    }
    return (c - s); // I accidentally flipped these two earlier, whoops
}
