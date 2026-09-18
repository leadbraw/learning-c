#include "contacts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// taken from test_contacts.c in module 06
static Contact make(const char *name, const char *email, int age) {
    Contact c;
    memset(&c, 0, sizeof c);
    strncpy(c.name, name, sizeof c.name - 1);
    strncpy(c.email, email, sizeof c.email - 1);
    c.age = age;
    return c;
}

static int strcmp_wrapper(const void *a, const void *b) {

    const Contact* con_a;
    const Contact* con_b;
    con_a = a;
    con_b = b;
    
    return strcmp(con_a->name, con_b->name);
}

int main(void) {
    Contact conlist[10];

    char* names[] = {"Bob", "Alice", "Zebra", "Noah", "Natalie", "Magnolia", "Lance", "Godrick", "Patches", "Rover"};
    for (int i = 0; i < 10; i++) {
        Contact con = make(names[i], "email@email.org", 25); // we're just sorting by name
        conlist[i] = con;
    }

    qsort(conlist, 10, sizeof(Contact), strcmp_wrapper);
    
    for (int i = 0; i < 10; i++) {
        printf("contact name: %s\n", conlist[i].name);
    }
    return 0;
}
