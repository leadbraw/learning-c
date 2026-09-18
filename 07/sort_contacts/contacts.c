#include "contacts.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Contacts {
    Contact* data;
    size_t len;
    size_t cap;
};

// utility function used by con_find()
static bool starts_with(const char *str, const char *pre) {
    while (*pre) {
        if (*str == '\0' || tolower((unsigned char) *str) != tolower((unsigned char) *pre)) {
            return false;
        }
        str++;
        pre++;
    }
    return true;
}

static int con_grow(Contacts* c) {
    Contact* tmp = realloc(c->data, c->cap * 2 * sizeof *c->data);
    if (!tmp) {
        return -1; 
    }
    else { 
        c->data = tmp; 
        c->cap *= 2;
        return 0;
    }
}

// here, pop is just used internally. as opposed to vec where it's exposed
static void con_pop(Contacts* c) {
    if (c->len == 0) return;
    c->len -= 1; // we'll just overwrite it on the next push
}

Contacts* con_new(void) {
    Contacts* c = malloc(sizeof(*c));
    if (!c) return NULL;
    c->data = malloc(8 * sizeof *c->data);
    if (!c->data) {
        free(c);
        return NULL;
    }
    c->len = 0;
    c->cap = 8;
    return c;    
}

int con_push(Contacts* c, Contact* con) {
    if (c->len == c->cap) {
        int grow_res = con_grow(c);
        assert(grow_res == 0);
    }
    c->data[c->len++] = *con; //idk if this assignment is right re: dereferencing
    return 0;
}

Contact* con_get(const Contacts* c, size_t i) {
    assert(i < c->len);
    return &c->data[i];    
}

size_t con_len(const Contacts* c) {
    return c->len;
}

void con_delete(Contacts* c, size_t i) {
    if (i >= c->len) return;
    if (i == c->len - 1) { con_pop(c); return; }
    
    memmove(c->data + i, c->data + i + 1, (c->len - i - 1) * sizeof *c->data);
    c->len -= 1;
    return;
}

// prefix, return first match. only checks names (not email)
Contact* con_find(Contacts* c, const char* str) {
    if (strlen(str) > 25) { return NULL; } // returning NULL on failure and error...

    for (size_t i = 0; i < c->len; i++) {
        if (starts_with(con_get(c, i)->name, str)) {
            return con_get(c, i);
        }
    }
    return NULL;
}

void con_free(Contacts* c) {
    if (!c) return;
    
    free(c->data);
    free(c);
}
