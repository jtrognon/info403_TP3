#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "TP3_VEURRIER_TROGNON_contact.h"
#include "TP3_VEURRIER_TROGNON_file.h"



// --------------------
// Actions sur contacts
// --------------------
// ajouter

Contact * create_contact(char * name, char * first_name, char * phone, char * mail)
{
    Contact * c = (Contact *) malloc(sizeof(Contact));
    strcpy(c->name, name);
    strcpy(c->first_name, first_name);
    strcpy(c->phone, phone);
    strcpy(c->mail, mail);

    return c;
}

// void get_contact(char ** name, char ** first_name, char ** phone, char ** mail);

// lister


void print_contact(Contact c, char * options)
{
    int nb_options = get_nb_options(options);

    if (nb_options < 0 || nb_options > 4)
    {
        exit(EXIT_FAILURE); // les options données sont vide
    }

    for (int i = 0; i < nb_options; i++)
    {
        char current_option = options[i]; // i+1 pour eviter le '['
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
            exit(EXIT_FAILURE);
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


