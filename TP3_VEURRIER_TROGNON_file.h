#ifndef __FILE_H_
#define __FILE_H_
#include "TP3_VEURRIER_TROGNON_contact.h"
#include "TP3_VEURRIER_TROGNON_hashtable.h"
#include "TP3_VEURRIER_TROGNON_tree.h"

#define MAX_SIZE NAME_MAX_LENGTH * 2 + PHONE_LENGTH + MAIL_MAX_LENGTH + 3 // +3 -> 3 * ','
typedef char line[MAX_SIZE];


void add_contact_to_f(char * file_name, char * name, char * first_name, char * phone, char * mail);

void print_contacts(char * file_name, char * options);

// supprimer
int get_line_nb_of_contact(char * file_name, int option_nb, char * value);
void remove_contact_from_f(char * file_name, char * name);


void find_contact_from_f(char * file_name, char * options, char * values);

// // extraire
int get_nb_options(char * options);
void extract_data_from_f(char * file_name, char * options);

// // fusionner
void merge_file(char * file_name1, char * file_name2);



// Aide
void print_help(void);

// Verification de fichier
void check_file(FILE * f);

// gestion des options
void arg_action(int argc, char * const argv[]);



// charger 
void load_h(HashTable h, char * file_name);

//sauvegarder
void save_h(HashTable h, char * file_name);

// Chargement de l'arbre binaire à l'aide d'un fichier
void load_tree(char * file, Node ** tree, char * options, bool without_dup);

#endif