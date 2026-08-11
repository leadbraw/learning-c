#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "linkedlist.h"

int main(void)
{
    /* single node */
    Node *n = node_new(42);
    assert(n != NULL);
    assert(node_val(n) == 42);
    assert(node_next(n) == NULL);
    free_all(n);

    /* 1,2,3 = 3 -> 2 -> 1 */
    Node *head = node_new(1);
    assert(head != NULL);
    head = push_front(head, 2);
    assert(head != NULL);
    head = push_front(head, 3);
    assert(head != NULL);

    assert(node_val(head) == 3);
    assert(node_val(node_next(head)) == 2);
    assert(node_val(node_next(node_next(head))) == 1);
    assert(node_next(node_next(node_next(head))) == NULL);

    size_t count = 0;
    for (const Node *cur = head; cur != NULL; cur = node_next(cur))
        count++;
    assert(count == 3);

    print_nodes(head); // use your eyes!
    printf("\n");

    free_all(head);

    // big ol list
    Node *big = node_new(0);
    assert(big != NULL);
    for (int i = 1; i < 100; i++) {
        big = push_front(big, i);
        assert(big != NULL);
    }
    assert(node_val(big) == 99);
    free_all(big);

    free_all(NULL);

    printf("all tests passed\n");
    return 0;
}
