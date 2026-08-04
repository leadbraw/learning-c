#include <stdio.h>

int main(void) {
    printf("char int: %zu bytes\n", sizeof(struct {char a; int b;}));
    printf("int char: %zu bytes\n", sizeof(struct {int a; char b;}));
    printf("char int char: %zu bytes\n", sizeof(struct {char a; int b; char c;}));
    printf("int char char: %zu bytes\n", sizeof(struct {int a; char b; char c;}));

    return 0;
}
