#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* node_new(const int value) {
    Node* head = malloc(sizeof(*head));
    if (!head) return NULL;
    head->next = NULL;
    head->val = value;
    return head;    
}

int node_val(const Node *n) {
    return n->val;
}

Node *node_next(const Node *n) {
    return n->next;
}

Node* push_front(Node* head, const int value) {
    Node* node = node_new(value);
    if (!node) return NULL;
    node->next = head;
    return node;
}

void print_nodes(Node* head) {
    printf("%d", head->val);
    Node* curr = head->next;
    while (curr) {
        printf(", ");
        printf("%d", curr->val);
        curr = curr->next;
    }
}

void free_all(Node* head) {
    Node* curr = head;
    Node* curr2 = head;
    while (curr) {
        curr2 = curr->next;
        free(curr);
        curr = curr2;
    }
}
