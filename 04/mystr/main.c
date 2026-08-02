#include <assert.h>
#include "mystr.h"

int main(void) {
    char buf[] = "abc";
    char* parts[5];
    assert(my_split(buf, ',', parts, 5) == 1);
    char buf2[] = "a,b,c";
    char* parts2[5];
    assert(my_split(buf2, ',', parts2, 5) == 3);
    char buf3[] = "";
    char* parts3[2];
    assert(my_split(buf3, ',', parts3, 2) == 1);
    char buf4[] = "a,,b";
    char* parts4[3];
    assert(my_split(buf4, ',', parts4, 3) == 3);
    char buf5[] = ",a,";
    char* parts5[3];
    assert(my_split(buf5, ',', parts5, 3) == 3);
    char buf6[] = "a,b,c,d";
    char* parts6[3];
    assert(my_split(buf6, ',', parts6, 2) == 2);
    return 0;
}
