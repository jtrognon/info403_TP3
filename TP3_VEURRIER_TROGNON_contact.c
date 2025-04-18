#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "TP3_VEURRIER_TROGNON_contact.h"
#include "TP3_VEURRIER_TROGNON_file.h"



// --------------------
// Actions sur contacts
// --------------------

// Permet de créer un contact et retourne son adresse
Contact * create_contact(char * name, char * first_name, char * phone, char * mail)
{

    Contact * c = (Contact *) malloc(sizeof(Contact));
    
    // Copie des informations dans les champs de contact
    strcpy(c->name, name);             // Copie le nom
    strcpy(c->first_name, first_name); // Copie le prénom
    strcpy(c->phone, phone);           // Copie le numéro de téléphone
    strcpy(c->mail, mail);             // Copie l'adresse mail

    return c; // Retourne l'adresse du contact créé
}

// void get_contact(char ** name, char ** first_name, char ** phone, char ** mail);

// lister

// Affiche les informations du contact selon les options données
void print_contact(Contact c, char * options)
{
    int nb_options = get_nb_options(options); // Récupère le nombre de champs à afficher

    if (nb_options < 0 || nb_options > 4) // Vérifie que le nombre d’options est valide (entre 1 et 4)
    {
        exit(EXIT_FAILURE); // les options données sont vide
    }

    // Parcours chaque caractère de la chaîne d'options
    for (int i = 0; i < nb_options; i++)
    {
        char current_option = options[i]; //Extrait l'option actuelle
        
        // Sélectionne l'information à afficher selon l'option
        switch (current_option)
        {
            case 'n':
            printf("%s%s", "Nom : ", c.name);
            break;
            case 'p':
            printf("%s%s", "Prénom : ", c.first_name);
            break;
            case 't':
            printf("%s%s", "Numéro de téléphone : ", c.phone);
            break;
            case 'm':
            printf("%s%s", "Mail : ", c.mail);
            break;
            default:
            exit(EXIT_FAILURE); // Si option inconnue, on quitte
            break;
        }
        
        if ((i+1) < nb_options){
            printf("%s", ", ");
        }

    }

    printf("\n");
}





// rechercher
// char * get_name(void);
// char * get_first_name(void);
// char * get_phone(void);
// char * get_mail(void);


