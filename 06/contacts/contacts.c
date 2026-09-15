#include "contacts.h"
#include <stdlib.h>

struct Contacts {
    Contact* data;
    size_t len;
    size_t cap;
};
