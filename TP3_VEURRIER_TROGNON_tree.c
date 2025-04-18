#include "TP3_VEURRIER_TROGNON_tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Node *create_tree(char option,Node *tree, Contact c,bool sans_doublons){
    if (tree == NULL){
        Node *new = (Node *) malloc(sizeof(Node));
        new->contact = c;
        new->left = NULL;
        new->right = NULL;


        return new;
    }

    int compare = compare_contacts(c, tree->contact,option);
    if (compare>0){
        tree->right = create_tree(option,tree->right,c,sans_doublons);
    }
    else if(compare<0 || (sans_doublons = false)){
        tree->left = create_tree(option,tree->left,c,sans_doublons);
    }
    else
   
    return tree;

}

int compare_contacts(Contact c1, Contact c2, char option){
    int res;
    switch(option){
        case 'n' :
            res = strcmp(c1.name,c2.name);
            break;
        case 'p' :
            res = strcmp(c1.first_name,c2.first_name);
            break;
        case 't' :
            res = strcmp(c1.phone,c2.phone);
            break;
        case 'm' :
            res = strcmp(c1.mail,c2.mail);
            break;
        default:
            return 0;
          
    }

}

// case 't':
//     if(first_val + 1 >= argc) {
//         fprintf(stderr, "Pas le bon nombre d'arguments\n");
//         exit(EXIT_FAILURE);
//     }

//     verify_arg(argv, first_val, 2);

//     char option = optarg;
//     char file = argv[optind]

//     File *f = fopen(file, "r");
//     while (fscanf(f, "%[^ ] %[^ ] %[^ ] %[^\n]\n", name, first_name, phone, mail) == 4){

//         Contact c = create_contact(name, first_name, phone, mail);
//         tree = create_tree(tree, c,option);
//     }
//     fclose(f);

//     File *f = fopen(file, "w");
//     fonction_qui_va_afficher(f,tree) jsp trop
//     fclose(f);
//     break;