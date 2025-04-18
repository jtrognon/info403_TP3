#include "TP3_VEURRIER_TROGNON_tree.h"
#include "TP3_VEURRIER_TROGNON_file.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void create_tree(char * option, Node ** tree, Contact c, bool without_dup){
    if (*tree == NULL){
        printf("name_t : %s\n", c.name);
        *tree = (Node *) malloc(sizeof(Node));
        (*tree)->contact = c;
        (*tree)->left = NULL;
        (*tree)->right = NULL;


    } else {
        int compare_1 = compare_contacts(c, (*tree)->contact,option[0]);
        int compare_2;

        if (without_dup){
            compare_2 = compare_contacts(c, (*tree)->contact,option[1]);
        }

        if (compare_1>0 || (without_dup && (compare_1 != compare_2) && (compare_1 + compare_2 > 0))){
            create_tree(option,&(*tree)->right,c,without_dup);
        }
        else if(compare_1<0 || ! without_dup || (without_dup && (compare_1 != compare_2))){
            create_tree(option,&(*tree)->left,c,without_dup);
        }
    }

}

int compare_contacts(Contact c1, Contact c2, char option){
    switch(option){
        case 'n' :
            return strcmp(c1.name,c2.name);
            break;
        case 'p' :
            return strcmp(c1.first_name,c2.first_name);
            break;
        case 't' :
            return strcmp(c1.phone,c2.phone);
            break;
        case 'm' :
            return strcmp(c1.mail,c2.mail);
            break;
        default:
            return 0;
          
    }
}

void write_tree_to_f(char * file_name, Node * tree)
{
    if (tree != NULL){

        char name[NAME_MAX_LENGTH+1];
        char first_name[NAME_MAX_LENGTH+1];
        char phone[PHONE_LENGTH+1];
        char mail[MAIL_MAX_LENGTH+1];
        
        printf("titi : %s\n", tree->contact.name);
        strcpy(name, tree->contact.name);
        strcpy(first_name, tree->contact.first_name);
        strcpy(phone, tree->contact.phone);
        strcpy(mail, tree->contact.mail);
        
        // add_contact_to_f(char * file_name, char * name, char * first_name, char * phone, char * mail)
        if (is_leaf(tree))
        {
            add_contact_to_f(file_name, name, first_name, phone, mail);
        } 
        else 
        {
            write_tree_to_f(file_name, tree->left);
            add_contact_to_f(file_name, name, first_name, phone, mail);
            write_tree_to_f(file_name, tree->right);
        }
    }
}

bool is_leaf(Node * tree)
{
    return tree->left == NULL && tree->right == NULL;
}

void free_tree(Node * tree)
{
    if (tree != NULL)
    {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}