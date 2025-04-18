#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "TP3_VEURRIER_TROGNON_main.h"
#include "TP3_VEURRIER_TROGNON_contact.h"
#include "TP3_VEURRIER_TROGNON_file.h"
#include "TP3_VEURRIER_TROGNON_hashtable.h"
#include "TP3_VEURRIER_TROGNON_tree.h"

int main(int argc, char * const argv[])
{
    char * file_name = "toto.txt";

    arg_action(argc, argv);

    return 0;
}



// Vérifie que l'option reçue possède bien le bon nombre de valeurs après elle
void verify_arg(char * const argv[], int index, int offset)
{
    for (int i = 0; i < offset; i++)
    {
        if (argv[index + i][0] == '-') // Si une option commence par '-', alors une valeur attendue est manquante
        {
            printf("%s%s\n", "verify_arg : il n'y a pas assez de valeurs pour l'option ", argv[index-1]);
            exit(EXIT_FAILURE); // On stop le programme dans ce cas
        }
    }
    
} 

// Analyse et exécution des actions en fonction des options passées en ligne de commande

void arg_action(int argc, char *const argv[])
{
    int opt;
    int first_val;

    while ((opt = getopt(argc, argv, "a:l:r:e:f:s:i:d:t:h")) != -1){
        first_val = optind - 1; // Position du premier argument après l'option
        switch (opt)
        {
        case 'a': // Ajouter un contact à un fichier
           if (first_val + 4 >= argc) { //Si le fichier n'a pas le bon nb d'arguments
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }
            verify_arg(argv, first_val, 5);

            char *name = optarg;                // Nom (déjà lu par getopt)
            char *first_name = argv[optind];    // Prénom
            char *phone = argv[optind + 1];     // Numéro de telephone
            char *mail = argv[optind + 2];      // Email
            char *file_name = argv[optind + 3]; // Nom du fichier de sauvegarde

            add_contact_to_f(file_name, name, first_name, phone, mail);
            optind += 4; // Avance le pointeur d'argument de 4 valeurs
            break;

        case 'l': // Lister les contacts
            if (first_val >= argc) {    
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 1);

            char *file_name1 = optarg; //récupère le nom du fichier en paramètre
            print_contacts(file_name1,"nptm");  // Affiche tous les paramètres
            break;
        
        case 'r': // Rechercher un contact
            if (first_val + 2 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }
            verify_arg(argv, first_val, 3);

            char *options = optarg;             // Options de recherche
            char *nom1 = argv[optind];          // Nom à rechercher
            char *file_name2 = argv[optind + 1];// Fichier dans lequel chercher
            
            find_contact_from_f(file_name2,options,nom1); 
            break;

        case 'e': // Extraire des informations spécifiques
            if (first_val + 1 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2);

            char *options1 = optarg;            // Champs à extraire (ex : nom, mail)
            char *file_name3 = argv[optind];    // Fichier source
            
            extract_data_from_f(file_name3,options1); 
            break;

        case 'h': // Affiche l'aide
            print_help();
            break;


        case 'f': // Fusionne deux fichiers
        // free(c);

            if (first_val + 1 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2);

            char *file_name4 = optarg;
            char *file_name5 = argv[optind];
            
            merge_file(file_name4,file_name5); 
            break;

        case 's': // Supprime un contact
            if (first_val + 1 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2);

            char *nom2 = optarg;                // Nom à supprimer
            char *file_name6 = argv[optind];    // Fichier cible
            
            remove_contact_from_f(file_name6,nom2); 
            break;
        case 'i': // Lance le menu interactif avec un fichier donné
            if (first_val >= argc)
            {
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 1);

            interactive_menu(optarg);
            break;
        case 't':
            if(first_val + 1 >= argc) {
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2); // Verifie que 2 arguments sont bien apssés en paramètre

            // Vérifie que l'argument d'option du tri ne contient qu’un seul caractère (ex : n)
            if (strlen(optarg) > 1){
                fprintf(stderr, "Une seule lettre de tri est attendue\n");
            }

            char * file = argv[optind]; // Récupère le nom du fichier fourni après l’option

            Node * tree = NULL; // Initialise l’arbre binaire a NULL

            //Appelle la fonction load_tree qui charge le fichier passé en paramètre dans l'arbre. On met without_dup en false 
            load_tree(file, &tree, optarg, false);

            FILE *f_write = fopen(file, "w"); // Ouvre le fichier pour le vider

            fclose(f_write); //Permet d'effacer le contenu du fichier qu'on vient d'ouvrir

            write_tree_to_f(file, tree); // Réécrit les contacts triés à partir de l’arbre dans le fichier

            free_tree(tree); //Libère la mémoire qu'on à donné à notre arbre 

            break;
        case 'd':
            if(first_val + 1 >= argc) {
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2); // Vérifie que l’on a bien 2 arguments après -d

                // Vérifie que l’argument d’option contient au plus 2 lettres
            if (strlen(optarg) > 2){
                fprintf(stderr, "Une à deux lettres de tri sont attendues\n");
            }

            char * file_d = argv[optind];

            Node * tree_d = NULL;

            // Charge les contacts dans un arbre tout en supprimant les doublons (without_dup qui est donc en true ici)
            load_tree(file_d, &tree_d, optarg, true);

            FILE *f_write_d = fopen(file_d, "w"); // Ouvre le fichier pour le vider

            fclose(f_write_d); //Permet d'effacer le contenu du fichier qu'on vient d'ouvrir

            write_tree_to_f(file_d, tree_d); // Réécrit dans le fichier les contacts sans doublons

            free_tree(tree_d); //Libère la mémoire qu'on à donné à notre arbre 
            break;
        default:
            fprintf(stderr, "Option invalide\n"); // Erreur si l'on rentre un choix autre que ceux possibles 
            break;
        }
    }

}

// Menu interactif
void interactive_menu(char *file_name)
{
    int choice;
    char name[NAME_MAX_LENGTH+1], first_name[NAME_MAX_LENGTH+1], phone[PHONE_LENGTH+1], mail[MAIL_MAX_LENGTH+1];
    HashTable h; // Déclaration de la table de hachage
    init_hashtable(h); // Initialisation de la table
    load_h(h, file_name); // Chargement des contacts depuis le fichier dans la table

    do {
        // Menu texte
        printf("Que souhaitez-vous faire ?\n");
        printf("1. Ajouter un contact\n");
        printf("2. Afficher tous les contacts\n");
        printf("3. Rechercher un contact\n");
        printf("4. Supprimer un contact\n");
        printf("5. Extraire du fichier des informations\n");
        printf("6. Afficher l'aide\n");
        printf("9. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        // Exécution selon le choix
        switch (choice) {
            case 1:
                insert_contact_to_hash(h); // Ajout dans la table de hachage
                break;

            case 2:
                list_contact_from_hash(h); // Affichage de tous les contacts
                break;

            case 3:
                find_contact_from_hash(h); // Recherche d'un contact
                break;

            case 4:
                remove_contact_from_hash(h); // Suppression d'un contact 
                break;

            case 5:
                extract_data_from_hash(h); // Extraction d'infos spécifiques
                break;

            case 6:
                print_help(); // Affichage de l'aide
                break;

            case 9:
                printf("Au revoir !\n"); // Quitte le programme
                break;

            default:
                printf("Choix invalide.\n"); //Erreur si l'utilisateur rentre un choix autre que ceux proposés 
        }
    } while (choice != 9); // Répéter tant que l'utilisateur ne quitte pas

    save_h(h, file_name); // Sauvegarde les données modifiées dans le fichier
}