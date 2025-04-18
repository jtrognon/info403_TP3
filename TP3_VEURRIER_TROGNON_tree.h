#ifndef TREE_H
#define TREE_H
#include "TP3_VEURRIER_TROGNON_contact.h"
#include <stdbool.h>

typedef struct node {
Contact contact;
struct node *left;
struct node *right;
} Node;


void create_tree(char * option, Node **tree_root, Contact c, bool without_dup);

int compare_contacts(Contact c1, Contact c2, char option);

void write_tree_to_f(char * file_name, Node * tree);

bool is_leaf(Node * tree);

void free_tree(Node * tree);

#endif