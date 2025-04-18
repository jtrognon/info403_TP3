#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "TP3_VEURRIER_TROGNON_file.h"
#include "TP3_VEURRIER_TROGNON_hashtable.h"
#include "TP3_VEURRIER_TROGNON_tree.h"

// Affichage de l'aide dans la console
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

// Regarde si le fichier donné est nul, si oui alors il renvoie une erreur et ferme le porgramme
void check_file(FILE * f)
{
    if (f == NULL)
    {
        perror("le fichier n'existe pas");
        exit(EXIT_FAILURE);
    }
}


// Ajout d'un contact dans le fichier
void add_contact_to_f(char * file_name, char * name, char * first_name, char * phone, char * mail)
{
    FILE * f = fopen(file_name, "a"); // fichier qui va recevoir un nouveau contact
    check_file(f);

    fprintf(f, "%s %s %s %s\n", name, first_name, phone, mail); // écriture du contact dans le fichier sous la forme "<nom> <prenom> <telephone> <mail>"

    fclose(f);
}


// affichage de chaque contact compris dans le fichier en fonction des options données (nom, preénom, ...)
void print_contacts(char * file_name, char * options)
{
    FILE * f = fopen(file_name, "r"); // fichier qui contient les contacts
    check_file(f);

    char name[NAME_MAX_LENGTH];
    char first_name[NAME_MAX_LENGTH];
    char phone[PHONE_LENGTH];
    int int_phone = 0;
    char mail[MAIL_MAX_LENGTH];

    int res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail); // récupération des infos du contact courant
    sprintf(phone, "%d", int_phone); // transformation en string

    while (res == 4) // 4 = nombre d'elements du fscanf
    {
        Contact * c = create_contact(name, first_name, phone, mail);

        print_contact(*c, options); // affichage du contact courant

        free(c); // libération du contact

        // prochain contact
        res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
        sprintf(phone, "%d", int_phone);
    }
    
    fclose(f);
}



// supprimer

// renvoie la ligne correspondant à la valeur donnée
int get_line_nb_of_contact(char * file_name, int option_nb, char * value)
{
    FILE * f = fopen(file_name, "r");
    check_file(f);

    int i = 0;
    int pos = -1; // position du contact recherché

    line line_tmp; // ligne courant
    char * value_tmp; // valeur recherché du contact courant 

    int res = fscanf(f, "%[^\n]\n", line_tmp); // ligne courante
    while (res == 1 && pos == -1)
    {
        value_tmp = strtok(line_tmp, " "); // première valeur de la ligne (nom)
        for (int i = 1; i <= option_nb; i++) // continue jusqu'à arriver au paramètre recherché
        {
            value_tmp = strtok(NULL, " ");
        }

        if (strcmp(value_tmp, value) == 0) // le contact a été trouvé
        {
            pos = i;
        }

        res = fscanf(f, "%[^\n]\n", line_tmp); // prochain contact
        i++;
    }

    fclose(f);
    return pos; // position du contact recherché, -1 sinon
}


// rajoute les zéros manquant lors de la convertion de int en string
void correct_phone_nb(char phone[PHONE_LENGTH])
{
    int n = strlen(phone); // taille du numéro sans les zéros à gauche
    int nb_zero = (PHONE_LENGTH) - n; // nombre de zéro à rajouter

    char correct_phone[PHONE_LENGTH]; // chaîne contenant le bon nombre de zéro

    for (int i = 0; i < nb_zero; i++) // ajout des zéros à gauche
    {
        correct_phone[i] = '0';
    }

    
    for (int i = 0; i < n; i++) // ajout du reste du numéro
    {
        correct_phone[i+nb_zero] = phone[n];
    }
    

    strcpy(phone, correct_phone); // modification de la chaine

}


// recherche de contact dans un fichier en fonction d'un paramètre en particulier
void find_contact_from_f(char * file_name, char * option, char * value)
{
    int field; // champ recherché (nom, prénom, ...)
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
        exit(EXIT_FAILURE); // le champ ne correspond pas à ceux disponibles
    }

    // position du contact recherché
    int line_nb = get_line_nb_of_contact(file_name, field, value);
    
    if (line_nb >= 0){ // le contact est dans le fichier

        FILE * f = fopen(file_name, "r");
        
        line dump; // ligne courante permettant d'arriver jusuq'à la ligne du contact recherché
        
        for (int i = 0; i < line_nb; i++) // saute les lignes
        {
            fscanf(f, "%[^\n]\n", dump);
        }
        
        
        char name[NAME_MAX_LENGTH];
        char first_name[NAME_MAX_LENGTH];
        int int_phone;
        char phone[PHONE_LENGTH];
        char mail[MAIL_MAX_LENGTH];
        
        // récupération de la ligne du contact recherché
        fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
        sprintf(phone, "%d", int_phone);
        correct_phone_nb(phone);
        
        // affichage du contact
        Contact * c = create_contact(name, first_name, phone, mail);
        print_contact(*c, "nptm");
        free(c);
        
        fclose(f);
    }
}



// retire un contact du fichier
void remove_contact_from_f(char * file_name, char * name)
{
    // position du contact à retirer
    int pos = get_line_nb_of_contact(file_name, 0, name);
    
    // le contact est dans le fichier
    if (pos != -1){
        FILE * f = fopen(file_name, "r");
        check_file(f);
        
        line * new_file_content; // buffer contenant les contact qui ne sont pas à supprimer
        line l; // ligne courante

        int i = 0;

        int res = fscanf(f, "%[^\n]\n", l); // ligne courante
        
        int size = 0;
        
        while (res == 1) // tant que l'on est pas à la fin du fichier 
        {
            if (i != pos){ // si ce n'est pas la ligne du contact à supprimer
                if (size == 0){ // le buffer est vide
                    new_file_content = (line *) malloc(sizeof(char) * MAX_SIZE + 1);
                } else {
                    new_file_content = (line *) realloc(new_file_content, (sizeof(char) * MAX_SIZE + 1) * (i+1));
                }
                strcpy(new_file_content[size], l); // ajoute la ligne
                size++; // taille du buffer
            } 
            i++; // numéro de ligne dans le fichier
            
            
            res = fscanf(f, "%[^\n]\n", l); // prochaine ligne
        }
        fclose(f);

        f = fopen(file_name, "w"); // même fichier mais en écriture pour tout écrire sauf la ligne concerné
        
        
        i = 0;
        
        while (i < size) // ne pas dépasser la taille du buffer
        {
            fputs(new_file_content[i], f); // écriture du buffer
            fputs("\n", f);
            i++;
        }

        free(new_file_content);
        fclose(f);
    }
}



// fusion de deux fichiers
void merge_file(char * file_name1, char * file_name2)
{
    FILE * f1 = fopen(file_name1, "a"); // écriture dans celui-ci
    FILE * f2 = fopen(file_name2, "r");

    line l; // ligne de tranfert entre les deux fichiers
    
    int res = fscanf(f2, "%[^\n]\n", l); // lecture dans le deuxième
    while (res == 1) // jusqu'à la fin du fichier
    {
        fprintf(f1, "%s\n", l); // écriture dans le premier

        res = fscanf(f2, "%[^\n]\n", l); // prochaine ligne
    }
    fclose(f1);
    fclose(f2);
}


// extraire des données en fonctions des champs donnés
void extract_data_from_f(char * file_name, char * options)
{
    print_contacts(file_name, options);
}

// nombre d'options données
int get_nb_options(char * options)
{
    return strlen(options);
}


// Charge la hashmap depuis un fichier
void load_h(HashTable h, char * file_name)
{
    FILE * f = fopen(file_name, "r"); // fichier qui contient la hashmap
    check_file(f);

    char name[NAME_MAX_LENGTH+1];
    char first_name[NAME_MAX_LENGTH+1];
    char phone[PHONE_LENGTH+1];
    int int_phone = 0;
    char mail[MAIL_MAX_LENGTH+1];

    // ligne courante
    int res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
    sprintf(phone, "%d", int_phone);

    while (res == 4) // 4 = nombre d'elements du fscanf
    {
        Contact * c = create_contact(name, first_name, phone, mail);

        add_contact(h, *c); // ajout du contact à la hashmap

        // prochaine ligne
        res = fscanf(f, "%[^ ] %[^ ] %d %s\n", name, first_name, &int_phone, mail);
        sprintf(phone, "%d", int_phone);

        free(c);
    }
    
    fclose(f);
}

// sauvegarde de la hashtable
void save_h(HashTable h, char * file_name)
{
    FILE * f = fopen(file_name, "w"); // fichier qui va contenir les contacts de la hashtable
    fclose(f);

    while (! is_empty(h))
    {
        Contact c = pop_contact(h); // récupération d'un contact
        
        add_contact_to_f(file_name, c.name, c.first_name, c.phone, c.mail);
    }
}





// chargement d'un fichier sous forme d'arbre et retire ou non les doublons
void load_tree(char * file, Node ** tree, char * options, bool without_dup){
    char name_t[NAME_MAX_LENGTH+1];
    char first_name_t[NAME_MAX_LENGTH+1];
    int phone_int;
    char phone_t[PHONE_LENGTH+1];
    char mail_t[MAIL_MAX_LENGTH+1];

    FILE *f_read = fopen(file, "r");

    // ligne courante
    int res_t = fscanf(f_read, "%[^ ] %[^ ] %d %s\n", name_t, first_name_t, &phone_int, mail_t);

    while (res_t == 4){
        sprintf(phone_t, "%d", phone_int); // convertion du numéro en chaine
        
        Contact * c = create_contact(name_t, first_name_t, phone_t, mail_t);

        create_tree(options, tree, *c, without_dup); // ajout dans l'arbre
        
        free(c);
        
        // prochaine ligne
        res_t = fscanf(f_read, "%[^ ] %[^ ] %d %s\n", name_t, first_name_t, &phone_int, mail_t);
    }

    fclose(f_read);   
}