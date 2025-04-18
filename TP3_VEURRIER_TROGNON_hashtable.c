#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "TP3_VEURRIER_TROGNON_hashtable.h"


//initialisation
void init_hashtable(HashTable h)
{
    for (int i = 0; i < SIZE; i++)
    {
        h[i] = NULL;
    }
    
}

int hash(char *name, char *first_name) 
{
    int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
    hash += name[i];
    }
    for (int i = 0; i < strlen(first_name); i++) {
    hash += first_name[i];
    }
    return hash % SIZE;
}


// Retire un contact de la Hashtable
Contact pop_contact(HashTable h)
{
    Contact c_tmp;
    int i = 0;
    bool found = false;
    while (i < SIZE && !found)
    {
        if (h[i] != NULL) 
        {
            c_tmp = h[i]->contact;
            Contact_List cl = h[i];
            h[i] = h[i]->next;
            free(cl);
            found = true;
        }
        i++;
    }

    return c_tmp;
}

bool is_empty(HashTable h)
{
    bool empty = true;
    int i = 0;
    
    while (i < SIZE && empty)
    {
        empty = h[i] == NULL;

        i++;
    }

    return empty;
}



void find_contact_from_hash(HashTable h)
{
    
    char name[NAME_MAX_LENGTH+1];
    get_name(name);
    char first_name[NAME_MAX_LENGTH+1];
    get_first_name(first_name);
    

    int hash_value = hash(name, first_name);

    Contact * c = (Contact *) malloc(sizeof(Contact));
    
    bool found = find_contact_from_list(c, h[hash_value], name, first_name);
    
    if (found)
    {
        print_contact(*c, "nptm");
    } 
    else
    {
        printf("Le contact n'est pas présent dans l'annuaire.");
    }


    free(c);
}

bool find_contact_from_list(Contact * c, Contact_List cl, char name[NAME_MAX_LENGTH+1], char first_name[NAME_MAX_LENGTH+1])
{
    bool found = false;
    while (cl != NULL && !found)
    {
        if ((strcmp(cl->contact.name, name) == 0) && (strcmp(cl->contact.first_name, first_name) == 0))
        {
            found = true;
            *c = (cl->contact);
        }

        cl = cl->next;
    }

    return found;
}

void get_name(char name[NAME_MAX_LENGTH+1])
{
    char n[NAME_MAX_LENGTH+1];

    do
    {
        printf("%s%d%s", "Nom du contact (0 < taille < ", NAME_MAX_LENGTH+1, ") : ");
        scanf("%s", n);
    } while (strlen(n) > NAME_MAX_LENGTH && strlen(n) <= 0);

    strcpy(name, n);
}

void get_first_name(char first_name[NAME_MAX_LENGTH+1])
{
    char fn[NAME_MAX_LENGTH+1];

    do
    {
        printf("%s%d%s", "Prénom du contact (0 < taille < ", NAME_MAX_LENGTH+1, ") : ");
        scanf("%s", fn);
    } while (strlen(fn) > NAME_MAX_LENGTH && strlen(fn) <= 0);

    strcpy(first_name, fn);
}



void extract_data_from_hash(HashTable h)
{
    char params[4];
    get_printing_parameters(params);

    for (int i=0; i < SIZE; i++)
    {
        print_contact_list(h[i], params);
    }
}


bool check_parameters(char params[4]){
    int length = strlen(params);
    bool is_valid = length < 5 && length > 0;

    int i = 0;
    while (i < length && is_valid)
    {
        is_valid = params[i] == 'n' || params[i] == 'p' || params[i] == 't' || params[i] == 'm';
        
        i++;
    }

    return is_valid;
}

void get_printing_parameters(char params[4]) // erreur : si chaîne > 4 donnée
{
    char p[4];
    printf("%s\n", "Veuillez choisir les paramètres d'extraction.");
    do {
        printf("%s\n%s\n", "Nom (n), Prénom (p), Téléphone (t) et/ou Mail (m).", "Votre Choix : ");
        scanf("%s", p);
    // } while(false);
    } while (! check_parameters(p));
    strcpy(params, p);
    // return params;
}

void print_contact_list(Contact_List cl, char * params)
{
    while (cl != NULL){
        print_contact(cl->contact, params);

        cl = cl->next;
    }
}



void remove_contact_from_hash(HashTable h)
{
    bool found = false;
    int i = 0;

    char name[NAME_MAX_LENGTH+1];
    char first_name[NAME_MAX_LENGTH+1];

    get_name(name);
    get_first_name(first_name);

    int index = hash(name, first_name);
    Contact_List cl = h[index];
    while (cl != NULL && ! found)
    {
        if (strcmp(cl->contact.name, name)  == 0&& strcmp(cl->contact.first_name, first_name) == 0)
        {
            found = true;
        } else {
            i ++;
        }
        cl = cl->next;
    }

    if (!found)
    {
        printf("%s%s%s%s%s", "Le contact ", name, " ", first_name, " n'est pas présent dans l'annuaire.\n");
    } 
    else if (i == 0)
    {
        cl = h[index];
        Contact_List cl_tmp = cl;
        h[index] = cl->next;
        free(cl_tmp);
    } 
    else
    {
        int j = 0;
        cl = h[index];
        while (j < (i-1))
        {
            cl = cl->next;
            
            j++;
        }

        Contact_List cl_tmp = cl->next;
        cl->next = cl->next->next;
        free(cl_tmp);
    }
}


void free_hash(HashTable h)
{
    for (int i=0; i < SIZE; i++)
    {
        Contact_List cl = h[i];
        
        while (cl != NULL){
            Contact_List cl_tmp = cl;

            cl = cl->next;
            free(cl_tmp);
        }
    }
}


void insert_contact_to_hash(HashTable h)
{
    char name[NAME_MAX_LENGTH+1];
    char first_name[NAME_MAX_LENGTH+1];
    char phone[PHONE_LENGTH+1];
    char mail[MAIL_MAX_LENGTH+1];

    //fgets qui prend le nom de la variable, le nb de caractères max a lire et stdin pour l'entrée)

    printf("Nom : ");
    scanf("%s", &name);

    printf("Prénom : ");
    scanf("%s", &first_name);

    printf("Téléphone : ");
    scanf("%s", &phone);

    printf("Email : ");
    scanf("%s", &mail);

    Contact * c = create_contact(name, first_name, phone, mail);

    add_contact(h, *c);

    free(c);
}

void add_contact(HashTable h, Contact c)
{
    int index = hash(c.name, c.first_name);

    Contact_List cl = malloc(sizeof(struct contact_list));
    cl->contact = c;
    cl->next = h[index];
    h[index] = cl;
}


void list_contact_from_hash(HashTable h){
    printf("----------------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        Contact_List cl = h[i];

        while (cl != NULL) {
            Contact c = cl->contact;
            printf("Nom : %s \n", c.name);
            printf("Prenom : %s \n", c.first_name);
            printf("Telephone : %s \n", c.phone);
            printf("Email : %s \n", c.mail);

            cl = cl->next;

            printf("----------------------------------\n");
        }
    }
}