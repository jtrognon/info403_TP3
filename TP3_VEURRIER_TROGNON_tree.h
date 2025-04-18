#ifndef TREE_H
#define TREE_H
#include "TP3_VEURRIER_TROGNON_contact.h"
#include <stdbool.h>

typedef struct node {
Contact contact;
struct node *left;
struct node *right;
} Node;


Node *create_tree(char option, Node *tree_root, Contact c, bool sans_doublons);


#endif