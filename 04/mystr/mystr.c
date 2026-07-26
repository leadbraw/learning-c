#include "mystr.h"


void _swap(char *p1, char *p2) {
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/* Artisan, farm-to-table string operations. */

size_t my_strlen(const char *s) {
    const char* c = s;
    while (*c) {
        c++;
    }
    return (c - s);
}


char* my_strcpy(char* dst, const char* src) {
    const char* s = src;
    char* d = dst;
    while (*s) {
        *d = *s;
        s++;
        d++;
    }
    *d = '\0';
    return dst;
}

int my_strcmp(const char* a, const char* b) {
    while ((*a == *b) && (*a) && (*b)) {
        a++;
        b++;
    }
    return (unsigned char) (a - b);
}

char* my_strchr(const char* s, char c) {
    while (*s) {
        if (*s == c) {
            return (char *) s;
        }
        s++;
    }
    if (c == '\0') {
        return (char*) s;
    } else {
        return NULL;
    }
}

void my_strrev(char* s) {
    if (!*s) return;
    int n = my_strlen(s);
    if (n == 1) return;
    char* l = s;
    char* r = &s[n - 1];

    while (l != r) {
        _swap(l, r);
    }
    return;
}

size_t my_split(char* s, char sep, char* parts[], size_t max_parts){
    /* it's like strtok() but better */

    
}
