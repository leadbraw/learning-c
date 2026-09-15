#include <stddef.h>

#ifndef CONTACTS_H
#define CONTACTS_H

typedef struct {
    char name[25];
    char email[75];
    int age;    
} Contact;

typedef struct Contacts Contacts;

Contacts* con_new(void);
int con_push(Contacts* c, Contact* con);
Contact* con_get(const Contacts* c, size_t i);
size_t con_len(const Contacts* c);
void con_delete(Contacts* c, size_t i);
Contact* con_find(Contacts* c, const char* str);
void con_free(Contacts* c);

#endif
