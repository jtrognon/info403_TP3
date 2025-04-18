#include "TP3_VEURRIER_TROGNON_tree.h"
#include "TP3_VEURRIER_TROGNON_file.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//Fonction récursive qui insère un contact dans un arbre binaire selon un critère de tri
void create_tree(char * option, Node ** tree, Contact c, bool without_dup){
    // Si l'arbre est vide à cette position (noeud NULL)
    if (*tree == NULL){
        printf("name_t : %s\n", c.name);
        *tree = (Node *) malloc(sizeof(Node));
        (*tree)->contact = c; // Initialise le contact
        (*tree)->left = NULL; // Sous arbre gauche NULL
        (*tree)->right = NULL; // Sous arbre droit NULL


    } else {
        // Compare les contacts selon le premier critère
        int compare_1 = compare_contacts(c, (*tree)->contact,option[0]);
        int compare_2;

        // Si on veut éviter les doublons, on fait une deuxième comparaison
        if (without_dup){
            compare_2 = compare_contacts(c, (*tree)->contact,option[1]);
        }

        // Cas ou le contact doit aller dans le sous-arbre droit :
        // soit il est "plus grand" selon compare_1, soit il est différent sur au moins un critère.
        if (compare_1>0 || (without_dup && (compare_1 != compare_2) && (compare_1 + compare_2 > 0))){
            create_tree(option,&(*tree)->right,c,without_dup); // On insert le contact récursivement à droite
        }

        // Cas où le contact doit aller à gauche :
        // soit il est "plus petit", soit sans gestion des doublons, soit les deux critères sont différents
        else if(compare_1<0 || ! without_dup || (without_dup && (compare_1 != compare_2))){
            create_tree(option,&(*tree)->left,c,without_dup);
        }
        // Si compare_1 == 0 et compare_2 == 0, alors c'est un doublon exact → on n'insère pas
    }

}

//Compare deux contacts selon un critère à l'aide de strcmp
int compare_contacts(Contact c1, Contact c2, char option){
    switch(option){
        case 'n' :
            return strcmp(c1.name,c2.name); // strcmp compare ici le nom de c1 et c2 et renvoie soit -1 ou 0 ou 1
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

// Parcourt l'arbre et écrit chaque contact dans un fichier.
void write_tree_to_f(char * file_name, Node * tree)
{
    if (tree != NULL){

        //Stock les variables de contacts
        char name[NAME_MAX_LENGTH+1];
        char first_name[NAME_MAX_LENGTH+1];
        char phone[PHONE_LENGTH+1];
        char mail[MAIL_MAX_LENGTH+1];
        
        // Copie les données du contact actuellement lu
        printf("titi : %s\n", tree->contact.name);
        strcpy(name, tree->contact.name);
        strcpy(first_name, tree->contact.first_name);
        strcpy(phone, tree->contact.phone);
        strcpy(mail, tree->contact.mail);
        
        // Si le noeud est une feuille sans enfant
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

// Détermine si un noeud est une feuille (pas de fils gauche ni droit).
bool is_leaf(Node * tree)
{
    return tree->left == NULL && tree->right == NULL;
}

// Libère la mémoire donnée a notre arbre
void free_tree(Node * tree)
{
    if (tree != NULL)
    {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}