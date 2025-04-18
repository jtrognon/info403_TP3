#ifndef __HASHMAP_H_
#define __HASHMAP_H_
#include "TP3_VEURRIER_TROGNON_contact.h"
#include <stdbool.h>
#define SIZE 100

typedef struct contact_list {
    Contact contact;
    struct contact_list *next;
} *Contact_List;

typedef Contact_List HashTable[SIZE];


void init_hashtable(HashTable h);
int hash(char *name, char *first_name);

// Renvoie la condition "La hashtable est vide (elle ne contient aucune liste de contacts)"
bool is_empty(HashTable h);

// Retire un contact de la Hashtable
void pop_contact(HashTable h, Contact * c);

// Ajout d'un contact
void add_contact(HashTable h, Contact_List c);

// Demande et ajoute un contact
void insert_contact_to_hash(HashTable h); 

// Liste des contacts de la hashtable
void list_contact_from_hash(HashTable h);

// Recherche d'un contact
void find_contact_from_list(Contact * c, Contact_List cl, char * name, char * first_name);
void get_name(char name[NAME_MAX_LENGTH]);
void get_first_name(char name[NAME_MAX_LENGTH]);
void find_contact_from_hash(HashTable h);

// Extraction d'informations
bool check_parameters(char * params);
void get_printing_parameters(char * params);
void print_contact_list(Contact_List cl, char * params);
void extract_data_from_hash(HashTable h);

// suppression d'un contact
void remove_contact_from_hash(HashTable h);

void free_hash(HashTable h); // Clément

#endif