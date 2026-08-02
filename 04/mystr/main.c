#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "mystr.h"

static void test_strlen(void)
{
    assert(my_strlen("") == 0);
    assert(my_strlen("a") == 1);
    assert(my_strlen("hello") == 5);
    assert(my_strlen("a b c") == 5); // spaces are chars too yknow...
    const char *s = "cross-check";
    assert(my_strlen(s) == strlen(s));
}

static void test_strcpy(void)
{
    char dst[32];
    assert(my_strcpy(dst, "hello") == dst);
    assert(strcmp(dst, "hello") == 0);

    my_strcpy(dst, ""); // need to terminate
    assert(dst[0] == '\0');

    char tight[6]; // last byte null
    my_strcpy(tight, "hello");
    assert(tight[5] == '\0');
}

static void test_strcmp(void)
{
    /* spec is sign, not magnitude — assert <0/==0/>0, never exact values */
    assert(my_strcmp("abc", "abc") == 0);
    assert(my_strcmp("", "") == 0);
    assert(my_strcmp("abc", "abd") < 0);
    assert(my_strcmp("abd", "abc") > 0);
    assert(my_strcmp("abc", "ab") > 0); // prefix: shorter compares less
    assert(my_strcmp("ab", "abc") < 0);
    assert(my_strcmp("", "a") < 0);
    assert(my_strcmp("a", "") > 0);
}

static void test_strchr(void)
{
    const char *s = "hello";
    assert(my_strchr(s, 'h') == s); // first char
    assert(my_strchr(s, 'l') == s + 2); // first 'l', not second
    assert(my_strchr(s, 'o') == s + 4);
    assert(my_strchr(s, 'z') == NULL);
    assert(my_strchr(s, '\0') == s + 5);
    assert(my_strchr("", 'a') == NULL);
    const char *e = "";
    assert(my_strchr(e, '\0') == e);
}

static void test_strrev(void)
{
    char odd[]  = "abcde";
    my_strrev(odd);
    assert(strcmp(odd, "edcba") == 0);

    char even[] = "abcd";
    my_strrev(even);
    assert(strcmp(even, "dcba") == 0);

    char two[]  = "ab";
    my_strrev(two);
    assert(strcmp(two, "ba") == 0);

    char one[]  = "x";
    my_strrev(one);
    assert(strcmp(one, "x") == 0);

    char none[] = "";
    my_strrev(none);
    assert(none[0] == '\0');

    char twice[] = "palindromes are not";
    my_strrev(twice);
    my_strrev(twice);
    assert(strcmp(twice, "palindromes are not") == 0);
}

static void test_split(void)
{
    char b1[] = "abc";
    char *p1[5];
    assert(my_split(b1, ',', p1, 5) == 1);
    assert(strcmp(p1[0], "abc") == 0);

    char b2[] = "a,b,c";
    char *p2[5];
    assert(my_split(b2, ',', p2, 5) == 3);
    assert(strcmp(p2[0], "a") == 0);
    assert(strcmp(p2[1], "b") == 0);
    assert(strcmp(p2[2], "c") == 0);

    char b3[] = "";
    char *p3[2];
    assert(my_split(b3, ',', p3, 2) == 1);
    assert(p3[0][0] == '\0');

    char b4[] = "a,,b";
    char *p4[3];
    assert(my_split(b4, ',', p4, 3) == 3);
    assert(strcmp(p4[1], "") == 0); // empty middle

    char b5[] = ",a,";
    char *p5[3];
    assert(my_split(b5, ',', p5, 3) == 3);
    assert(strcmp(p5[0], "") == 0);
    assert(strcmp(p5[1], "a") == 0);
    assert(strcmp(p5[2], "") == 0);

    char b6[] = "a,b,c,d"; // max_parts < token count
    char *p6[2];
    assert(my_split(b6, ',', p6, 2) == 2);
    assert(strcmp(p6[0], "a") == 0);
    assert(strcmp(p6[1], "b") == 0);
    assert(strcmp(b6 + 4, "c,d") == 0);

    char b7[] = "a,b";
    assert(my_split(b7, ',', NULL, 0) == 0); // note max_parts is 0
    assert(strcmp(b7, "a,b") == 0); // make sure string untouched

    char b8[] = "a.b,c";
    char *p8[3];
    assert(my_split(b8, '.', p8, 3) == 2);
    assert(strcmp(p8[1], "b,c") == 0);
}

int main(void)
{
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_strchr();
    test_strrev();
    test_split();
    printf("all tests passed\n");
    return 0;
}
