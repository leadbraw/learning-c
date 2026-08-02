#include "mystr.h"


static void swap(char *p1, char *p2) {
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
    while ((*a == *b) && *a) {
        a++;
        b++;
    }
    return (unsigned char) *a - (unsigned char) *b;
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
    char* l = s;
    char* r = &s[n - 1];

    while (l < r) {
        swap(l, r);
        r--;
        l++;
    }
    return;
}

size_t my_split(char* s, char sep, char* parts[], size_t max_parts) {
    /* it's like strtok() but better */

    char* start = s;
    char* p = start;
    size_t n = 0;
    while (*p) {
        if (*p == sep) {
            if (n < max_parts) {
                *p = '\0';
                parts[n] = start;
                n += 1;
                start = p + 1;                
            } else { break; }
        }
        p++;
    }
    if (n < max_parts) {
        parts[n] = start;
        n++;
    }
    return n;
}

