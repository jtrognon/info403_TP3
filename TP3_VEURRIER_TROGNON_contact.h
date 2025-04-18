#ifndef __CONTACT_H_
#define __CONTACT_H_
#include <stdio.h>
#define NAME_MAX_LENGTH 100
#define PHONE_LENGTH 10
#define MAIL_MAX_LENGTH 100

typedef struct 
{
    char name[NAME_MAX_LENGTH+1];
    char first_name[NAME_MAX_LENGTH+1];
    char phone[PHONE_LENGTH+1];
    char mail[MAIL_MAX_LENGTH+1];
} Contact;



// typedef struct
// {
//     Contact * * contacts;
//     int size;
// } Hashmap;


//Contact * REMOVED = (Contact *) (-1);

// --------------------
// Actions sur contacts
// --------------------

// ajouter
Contact * create_contact(char * name, char * first_name, char * phone, char * mail);
// void get_contact(char ** name, char ** first_name, char ** phone, char ** mail);

// lister
void print_contact(Contact c, char * options);

// ------------------------
// Actions liés aux options
// ------------------------

// -a : ajouter un contact

// -l : lister contacts

// -h : afficher l'aide

// -r : rechercher un contact

// -e [<params>] : extraire du fichier les différents données lié au paramètres entre []

// -s : supprimer un contact

// -f : fusionner deux fichiers dans le premier
#endif