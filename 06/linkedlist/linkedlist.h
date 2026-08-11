#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;

Node* node_new(const int value);
Node* push_front(Node* head, const int value);
void print_nodes(Node* head);
void free_all(Node* head);
int   node_val(const Node *n);
Node *node_next(const Node *n);

#endif
