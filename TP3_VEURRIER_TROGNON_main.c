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

    // printf("%d\n", hash("TROGNON", "Julie"));

    arg_action(argc, argv);

    // HashTable h;
    // init_hashtable(h);
    

    // Contact * c1 = create_contact("toto", "celia", "0102030405", "toto@mail.com");
    // Contact * c2 = create_contact("toto", "alice", "0102030405", "toto@mail.com");
    // Contact * c3 = create_contact("toto", "calie", "0102030405", "toto@mail.com");



    // Contact_List cl = (Contact_List) malloc(sizeof(struct contact_list));
    // cl->contact = *c1;
    // cl->next = (Contact_List) malloc(sizeof(struct contact_list));
    // cl->next->contact = *c2;
    // cl->next->next = (Contact_List) malloc(sizeof(struct contact_list));
    // cl->next->next->contact = *c3;
    // cl->next->next->next = NULL;

    // h[hash("toto", "calie")] = cl;

    // load_h(h, "test.txt");
    // save_h(h, "test.txt");

    // find_contact_from_hash(h);
    // remove_contact_from_hash(h);

    // insert_contact_to_hash(h);
    // list_contact_from_hash(h);

    // extract_data_from_hash(h);

    // free(cl->next->next);
    // free(cl->next);
    // free(cl);

    // free_hash(h);

    // free(c1);
    // free(c2);
    // free(c3);

    return 0;
}



// verify argv values
void verify_arg(char * const argv[], int index, int offset)
{
    for (int i = 0; i < offset; i++)
    {
        if (argv[index + i][0] == '-')
        {
            printf("%s%s\n", "verify_arg : il n'y a pas assez de valeurs pour l'option ", argv[index-1]);
            exit(EXIT_FAILURE);
        }
    }
    
} 

// Gestion des options
void arg_action(int argc, char *const argv[])
{
    int opt;
    int first_val;

    while ((opt = getopt(argc, argv, "a:l:r:e:f:s:i:d:t:h")) != -1){
        first_val = optind - 1; // -1 pour aller au premier argument
        switch (opt)
        {
        case 'a':
           if (first_val + 4 >= argc) {
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }
            verify_arg(argv, first_val, 5);

            char *name = optarg;                
            char *first_name = argv[optind];    
            char *phone = argv[optind + 1];
            char *mail = argv[optind + 2];
            char *file_name = argv[optind + 3];

            add_contact_to_f(file_name, name, first_name, phone, mail);
            optind += 4;
            break;

        case 'l':
            if (first_val >= argc) {    //a voir comment rendre ca plus joli et surtout que ca marche mieux 
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 1);

            char *file_name1 = optarg;
            print_contacts(file_name1,"nptm"); 
            break;
        
        case 'r':
            if (first_val + 2 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }
            verify_arg(argv, first_val, 3);

            char *options = optarg;
            char *nom1 = argv[optind];
            char *file_name2 = argv[optind + 1];
            
            find_contact_from_f(file_name2,options,nom1); 
            break;

        case 'e':
            if (first_val + 1 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2);

            char *options1 = optarg;
            char *file_name3 = argv[optind];
            
            extract_data_from_f(file_name3,options1); 
            break;

        case 'h':
            print_help();
            break;


        case 'f':
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

        case 's':
            if (first_val + 1 >= argc) {   
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }

            verify_arg(argv, first_val, 2);

            char *nom2 = optarg;
            char *file_name6 = argv[optind];
            
            remove_contact_from_f(file_name6,nom2); 
            break;
        case 'i':
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
        
            verify_arg(argv, first_val, 2);
        
            if (strlen(optarg) > 1){
                fprintf(stderr, "Une seule lettre de tri est attendue\n");
            }

            char * file = argv[optind];

            
            Node * tree = NULL;
            
            load_tree(file, &tree, optarg, false);

            FILE *f_write = fopen(file, "w");
            fclose(f_write);
            write_tree_to_f(file, tree);
            free_tree(tree);
            break;
        case 'd':
            if(first_val + 1 >= argc) {
                fprintf(stderr, "Pas le bon nombre d'arguments\n");
                exit(EXIT_FAILURE);
            }
        
            verify_arg(argv, first_val, 2);

            if (strlen(optarg) > 2){
                fprintf(stderr, "Une à deux lettres de tri sont attendues\n");
            }

            char * file_d = argv[optind];

            
            Node * tree_d = NULL;
            
            load_tree(file_d, &tree_d, optarg, true);

            FILE *f_write_d = fopen(file_d, "w");
            fclose(f_write_d);
            write_tree_to_f(file_d, tree_d);
            free_tree(tree_d);
            break;
        default:
                fprintf(stderr, "Option invalide\n");
                break;

        }
    }

}

void interactive_menu(char *file_name)
{
    int choice;
    char name[NAME_MAX_LENGTH+1], first_name[NAME_MAX_LENGTH+1], phone[PHONE_LENGTH+1], mail[MAIL_MAX_LENGTH+1];
    HashTable h;
    init_hashtable(h);
    load_h(h, file_name);

    do {
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

        switch (choice) {
            case 1:
                insert_contact_to_hash(h);
                break;

            case 2:
                list_contact_from_hash(h);
                break;

            case 3:
                find_contact_from_hash(h);
                break;

            case 4:
                remove_contact_from_hash(h);
                break;

            case 5:
                extract_data_from_hash(h);
                break;

            case 6:
                print_help();
                break;
            case 9:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 9);

    save_h(h, file_name);
}