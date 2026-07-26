#ifndef MYSTR_H
#define MYSTR_H

#include <stddef.h>

size_t my_strlen(const char *s);
char* my_strcpy(char* dst, const char* src);
int my_strcmp(const char* a, const char* b);
char* my_strchr(const char* s, char c);
void my_strrev(char* s);
size_t my_split(char* s, char sep, char* parts[], size_t max_parts);

#endif
