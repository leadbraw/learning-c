/* Data-layer tests for contacts.c — no stdin, no files.
 *
 * Build & run:
 *   gcc -std=c99 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g \
 *       test_contacts.c contacts.c -o test_contacts && ./test_contacts
 *
 * Valgrind (no sanitizers):
 *   gcc -std=c99 -Wall -Wextra -Wpedantic -g test_contacts.c contacts.c -o test_contacts_vg
 *   valgrind --leak-check=full --show-leak-kinds=all ./test_contacts_vg
 *
 * Release-mode check (asserts compiled out) — exercises the growth path:
 *   gcc -std=c99 -DNDEBUG -fsanitize=address,undefined -g \
 *       test_contacts.c contacts.c -o test_contacts_ndebug && ./test_contacts_ndebug
 */
#include <stdio.h>
#include <string.h>
#include "contacts.h"

static int checks = 0, failures = 0;

#define CHECK(cond) do { \
    checks++; \
    if (!(cond)) { failures++; printf("  FAIL %s:%d: %s\n", __func__, __LINE__, #cond); } \
} while (0)

static Contact make(const char *name, const char *email, int age) {
    Contact c;
    memset(&c, 0, sizeof c);
    strncpy(c.name, name, sizeof c.name - 1);
    strncpy(c.email, email, sizeof c.email - 1);
    c.age = age;
    return c;
}

static void push(Contacts *c, const char *name, int age) {
    Contact x = make(name, "x@example.com", age);
    con_push(c, &x);
}

static void test_new_empty(void) {
    Contacts *c = con_new();
    CHECK(c != NULL);
    CHECK(con_len(c) == 0);
    CHECK(con_find(c, "A") == NULL);
    CHECK(con_find(c, "") == NULL);
    con_free(c);
}

static void test_free_null(void) {
    con_free(NULL); /* must not crash */
    CHECK(1);
}

static void test_push_get(void) {
    Contacts *c = con_new();
    Contact a = make("Ada", "ada@example.com", 36);
    CHECK(con_push(c, &a) == 0);
    CHECK(con_len(c) == 1);
    CHECK(strcmp(con_get(c, 0)->name, "Ada") == 0);
    CHECK(strcmp(con_get(c, 0)->email, "ada@example.com") == 0);
    CHECK(con_get(c, 0)->age == 36);
    con_free(c);
}

static void test_push_copies_value(void) {
    Contacts *c = con_new();
    Contact a = make("Ada", "ada@example.com", 36);
    con_push(c, &a);
    strcpy(a.name, "Changed");
    a.age = 99;
    CHECK(strcmp(con_get(c, 0)->name, "Ada") == 0);
    CHECK(con_get(c, 0)->age == 36);
    con_free(c);
}

static void test_growth(void) {
    Contacts *c = con_new();
    char name[25];
    for (int i = 0; i < 1000; i++) {
        snprintf(name, sizeof name, "n%d", i);
        push(c, name, i);
    }
    CHECK(con_len(c) == 1000);
    int idx[] = {0, 7, 8, 9, 15, 16, 17, 500, 999};
    for (size_t k = 0; k < sizeof idx / sizeof idx[0]; k++) {
        snprintf(name, sizeof name, "n%d", idx[k]);
        CHECK(con_get(c, idx[k])->age == idx[k]);
        CHECK(strcmp(con_get(c, idx[k])->name, name) == 0);
    }
    con_free(c);
}

static Contacts *abcd(void) {
    Contacts *c = con_new();
    push(c, "A", 0); push(c, "B", 1); push(c, "C", 2); push(c, "D", 3);
    return c;
}

static void test_delete_middle(void) {
    Contacts *c = abcd();
    con_delete(c, 1);
    CHECK(con_len(c) == 3);
    CHECK(strcmp(con_get(c, 0)->name, "A") == 0);
    CHECK(strcmp(con_get(c, 1)->name, "C") == 0);
    CHECK(strcmp(con_get(c, 2)->name, "D") == 0);
    con_free(c);
}

static void test_delete_first(void) {
    Contacts *c = abcd();
    con_delete(c, 0);
    CHECK(con_len(c) == 3);
    CHECK(strcmp(con_get(c, 0)->name, "B") == 0);
    CHECK(strcmp(con_get(c, 2)->name, "D") == 0);
    con_free(c);
}

static void test_delete_last(void) {
    Contacts *c = abcd();
    con_delete(c, 3);
    CHECK(con_len(c) == 3);
    CHECK(strcmp(con_get(c, 2)->name, "C") == 0);
    con_free(c);
}

static void test_delete_only_then_push(void) {
    Contacts *c = con_new();
    push(c, "Solo", 1);
    con_delete(c, 0);
    CHECK(con_len(c) == 0);
    CHECK(con_find(c, "Solo") == NULL);
    push(c, "Again", 2);
    CHECK(con_len(c) == 1);
    CHECK(strcmp(con_get(c, 0)->name, "Again") == 0);
    con_free(c);
}

static void test_delete_out_of_range(void) {
    Contacts *c = abcd();
    con_delete(c, 4);
    con_delete(c, (size_t)-1); /* what main's `del -1` becomes after int -> size_t */
    CHECK(con_len(c) == 4);
    CHECK(strcmp(con_get(c, 3)->name, "D") == 0);
    Contacts *e = con_new();
    con_delete(e, 0); /* empty book */
    CHECK(con_len(e) == 0);
    con_free(e);
    con_free(c);
}

static void test_delete_across_growth(void) {
    Contacts *c = con_new();
    char name[25];
    for (int i = 0; i < 20; i++) { snprintf(name, sizeof name, "n%d", i); push(c, name, i); }
    for (int i = 19; i >= 0; i -= 2) con_delete(c, (size_t)i); /* remove odd ages from the back */
    CHECK(con_len(c) == 10);
    for (size_t i = 0; i < con_len(c); i++) CHECK(con_get(c, i)->age == (int)(i * 2));
    while (con_len(c) > 0) con_delete(c, 0);
    CHECK(con_len(c) == 0);
    con_free(c);
}

static void test_find_prefix(void) {
    Contacts *c = con_new();
    push(c, "Ada", 1); push(c, "Adam", 2); push(c, "Bob", 3);
    CHECK(con_find(c, "Ada") == con_get(c, 0));   /* first match wins */
    CHECK(con_find(c, "Ad") == con_get(c, 0));
    CHECK(con_find(c, "Adam") == con_get(c, 1));
    CHECK(con_find(c, "B") == con_get(c, 2));
    CHECK(con_find(c, "Bobby") == NULL);          /* query longer than name */
    CHECK(con_find(c, "Z") == NULL);
    CHECK(con_find(c, "") == con_get(c, 0));      /* empty prefix matches anything */
    con_free(c);
}

static void test_find_max_length_name(void) {
    Contacts *c = con_new();
    const char *n24 = "ABCDEFGHIJKLMNOPQRSTUVWX"; /* 24 chars: fills name[25] exactly */
    push(c, n24, 1);
    CHECK(strlen(con_get(c, 0)->name) == 24);
    CHECK(con_find(c, n24) == con_get(c, 0));
    CHECK(con_find(c, "ABCDEFGHIJKLMNOPQRSTUVWXY") == NULL);  /* 25 chars */
    CHECK(con_find(c, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == NULL); /* 26 chars */
    con_free(c);
}

static void note_find_case(void) {
    /* Not counted as a failure: the spec's example is `add Ada,...` then `find ada`. */
    Contacts *c = con_new();
    push(c, "Ada", 1);
    printf("  NOTE: find(\"ada\") on \"Ada\" -> %s\n", con_find(c, "ada") ? "match" : "no match");
    con_free(c);
}

int main(void) {
    test_new_empty();
    test_free_null();
    test_push_get();
    test_push_copies_value();
    test_growth();
    test_delete_middle();
    test_delete_first();
    test_delete_last();
    test_delete_only_then_push();
    test_delete_out_of_range();
    test_delete_across_growth();
    test_find_prefix();
    test_find_max_length_name();
    note_find_case();

    printf("%d/%d checks passed\n", checks - failures, checks);
    return failures != 0;
}
