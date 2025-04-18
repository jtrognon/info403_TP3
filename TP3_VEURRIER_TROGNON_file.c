#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "TP3_VEURRIER_TROGNON_file.h"
#include "TP3_VEURRIER_TROGNON_hashtable.h"

// Aide
void print_help(void)
{
    printf("%s", "• -a : ajouter un contact \n\
• -l : lister les contacts. Les informations seront écrites sur la sortie standard.\n\
• -h : afficher l’aide \n\
• -r : rechercher un contact. Le contact sera recherché par nom (option n), téléphone (option t) ou mail (option m). \n\
\tUne seule lettre possible Le contact sera écrit sur la sortie standard. \n\
• -e [nptm] : extraire du fichier les noms, prénoms, numéros de téléphone, adresses mail. Pluisieurs lettres possibles.\n\
\tLes informations seront écrites sur la sortie standard. \n\
• -s : supprimer un contact \n\
• -f : fusionner deux fichiers. Le résultat sera écrit dans le premier fichier\n");
}

void check_file(FILE * f)
{
    if (f == NULL)
    {
        perror("le fichier n'existe pas");
        exit(EXIT_FAILURE);
    }
}


// Ajout d'un contact
void add_contact_to_f(char * file_name, char * name, char * first_name, char * phone, char * mail)
{
    FILE * f = fopen(file_name, "a");
    check_file(f);

    fprintf(f, "%s %s %s %s\n", name, first_name, phone, mail);

    fclose(f);
}


void print_contacts(char * file_name, char * options)
{
    FILE * f = fopen(file_name, "r");
    check_file(f);

    char name[NAME_MAX_LENGTH];
    char first_name[NAME_MAX_LENGTH];
    char phone[PHONE_LENGTH];
    int int_phone;
    char mail[MAIL_MAX_LENGTH];

    int res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
    sprintf(phone, "%d", int_phone);

    while (res == 4) // 4 = nombre d'elements du fscanf
    {
        Contact * c = create_contact(name, first_name, phone, mail);

        print_contact(*c, options);

        free(c);

        res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
        sprintf(phone, "%d", int_phone);
    }
    
    fclose(f);
}



// supprimer

// renvoie la ligne a supprimer
int get_line_nb_of_contact(char * file_name, int option_nb, char * value)
{
    FILE * f = fopen(file_name, "r");
    check_file(f);

    int i = 0;
    int pos = -1;

    line line_tmp;
    char * value_tmp;

    int res = fscanf(f, "%[^\n]\n", line_tmp);
    while (res == 1 && pos == -1)
    {
        value_tmp = strtok(line_tmp, " ");
        for (int i = 1; i < option_nb; i++)
        {
            value_tmp = strtok(NULL, " ");
        }

        if (strcmp(value_tmp, value) == 0)
        {
            pos = i;
        }

        res = fscanf(f, "%[^\n]\n", line_tmp);
        i++;
    }

    fclose(f);
    return pos;
}



void correct_phone_nb(char phone[PHONE_LENGTH])
{
    int n = strlen(phone);
    int nb_zero = (PHONE_LENGTH) - n;

    char correct_phone[PHONE_LENGTH];

    for (int i = 0; i < nb_zero; i++)
    {
        correct_phone[i] = '0';
    }

    
    for (int i = 0; i < n; i++)
    {
        correct_phone[i+nb_zero] = phone[n];
    }
    

    strcpy(phone, correct_phone);

}



void find_contact_from_f(char * file_name, char * option, char * value)
{
    int field;
    if (strcmp(option, "n") == 0)
    {
        field = 0;
    }
    else if (strcmp(option, "t") == 0)
    {
        field = 2;
        
    }
    else if (strcmp(option, "m") == 0)
    {
        field = 3;
    }
    else
    {
        exit(EXIT_FAILURE);
    }

    int line_nb = get_line_nb_of_contact(file_name, field, value);
    
    if (line_nb >= 0){

        FILE * f = fopen(file_name, "r");
        
        line dump;
        
        for (int i = 0; i < line_nb; i++)
        {
            fscanf(f, "%s\n", dump);
        }
        
        
        char name[NAME_MAX_LENGTH];
        char first_name[NAME_MAX_LENGTH];
        int int_phone;
        char phone[PHONE_LENGTH];
        char mail[MAIL_MAX_LENGTH];
        
        fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
        sprintf(phone, "%d", int_phone);
        correct_phone_nb(phone);
        
        Contact * c = create_contact(name, first_name, phone, mail);
        print_contact(*c, "nptm");
        free(c);
        
        fclose(f);
    }
}



void remove_contact_from_f(char * file_name, char * name)
{
    int pos = get_line_nb_of_contact(file_name, 0, name);
    
    if (pos != -1){
        FILE * f = fopen(file_name, "r");
        check_file(f);
        
        line * new_file_content;
        line l;

        int i = 0;

        int res = fscanf(f, "%[^\n]\n", l);
        
        int size = 0;
        
        while (res == 1)
        {
            if (i != pos){
                if (size == 0){
                    new_file_content = (line *) malloc(sizeof(char) * MAX_SIZE + 1);
                } else {
                    new_file_content = (line *) realloc(new_file_content, (sizeof(char) * MAX_SIZE + 1) * (i+1));
                }
                strcpy(new_file_content[size], l);
                printf("%s\n", l);
                size++;
            } 
            i++;
            
            
            res = fscanf(f, "%[^\n]\n", l);
        }
        fclose(f);

        f = fopen(file_name, "w");
        
        
        i = 0;
        
        while (i < size)
        {
            fputs(new_file_content[i], f);
            fputs("\n", f);
            i++;
        }

        free(new_file_content);
        fclose(f);
    }
}



// fusionner
void merge_file(char * file_name1, char * file_name2)
{
    FILE * f1 = fopen(file_name1, "a");
    FILE * f2 = fopen(file_name2, "r");

    line l;
    
    int res = fscanf(f2, "%s\n", l);
    while (res == 1)
    {
        fprintf(f1, "%s\n", l);

        res = fscanf(f2, "%s\n", l);
    }
    fclose(f1);
    fclose(f2);
}


// extraire
void extract_data_from_f(char * file_name, char * options)
{
    print_contacts(file_name, options);
}


int get_nb_options(char * options)
{
    return strlen(options);
}


// Charge
void load_h(HashTable h, char * file_name)
{
    FILE * f = fopen(file_name, "r");
    check_file(f);

    char name[NAME_MAX_LENGTH+1];
    char first_name[NAME_MAX_LENGTH+1];
    char phone[PHONE_LENGTH+1];
    int int_phone = 0;
    char mail[MAIL_MAX_LENGTH+1];

    int res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
    sprintf(phone, "%d", int_phone);

    while (res == 4) // 4 = nombre d'elements du fscanf
    {
        Contact * c = create_contact(name, first_name, phone, mail);

        print_contact(*c, "np");

        add_contact(h, *c);

        res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
        sprintf(phone, "%d", int_phone);

        free(c);
    }
    
    fclose(f);
}

void save_h(HashTable h, char * file_name)
{
    FILE * f = fopen(file_name, "w");
    fclose(f);

    while (! is_empty(h))
    {
        Contact c = pop_contact(h);
        
        add_contact_to_f(file_name, c.name, c.first_name, c.phone, c.mail);
    }
}