#include "memo_rpg.h"

/**
 * Initialise la position de départ des joueurs sur la bordure du plateau 6x6.
 * Les joueurs commencent sur des cases neutres pour éviter les monstres au spawn.
 */
void depart(Personnage tab_joueurs[], int nb_joueurs) { 
    for (int i = 0; i < nb_joueurs; i++) {
        // Initialisation de l'inventaire et de l'état
        tab_joueurs[i].aLarme = 0;
        tab_joueurs[i].aLeTresor = 0;
        tab_joueurs[i].arme_actuelle = EPEE; 

        // Placement stratégique sur les bords (indices 0 ou 5)
        if (i == 0) { // Nord
            tab_joueurs[i].ligne = 0; 
            tab_joueurs[i].colonne = 2;
        }
        else if (i == 1) { 
            if (nb_joueurs == 2) { // Face à face Sud si seulement 2 joueurs
                tab_joueurs[i].ligne = 5; 
                tab_joueurs[i].colonne = 2; 
            } else { // Est
                tab_joueurs[i].ligne = 2;
                tab_joueurs[i].colonne = 5;
            }
        }
        else if (i == 2) { // Sud
            tab_joueurs[i].ligne = 5;
            tab_joueurs[i].colonne = 2;
        }
        else if (i == 3) { // Ouest
            tab_joueurs[i].ligne = 2;
            tab_joueurs[i].colonne = 0;
        }
    }
}

/**
 * Permet à chaque joueur de choisir un personnage unique.
 * Gère la duplication pour qu'un personnage ne soit pas choisi deux fois.
 */
void select_perso(Personnage tab_joueurs[], int nb_joueurs) {
    int choix = 0;
    int deja_pris[4] = {0, 0, 0, 0}; // Tableau de drapeaux pour les 4 classes

    for (int i = 0; i < nb_joueurs; i++) {
        printf("\n--- JOUEUR %d ---\n", i + 1);
        printf("Choisissez votre heros :\n");
        printf("1: GANDALF\n2: TAURIEL\n3: GOLLUM\n4: GIMLI\nChoix : ");
        
        do {
            if (scanf("%d", &choix) != 1) {
                while(getchar() != '\n'); // Nettoyage du buffer en cas de saisie de texte
            }

            if (choix < 1 || choix > 4 || deja_pris[choix-1] == 1) {
                printf("Ce heros est deja sur le terrain ou n'existe pas. Recommencez : ");
            }
        } while(choix < 1 || choix > 4 || deja_pris[choix-1] == 1);

        // Enregistrement du choix (conversion index 0-3 pour l'enum Classe)
        tab_joueurs[i].perso = (Classe)(choix-1); 
        
        if (choix == 1){ 
            strcpy(tab_joueurs[i].nomJoueur, "Gandalf");
            tab_joueurs[i].arme_a_trouver = BATON; 
            deja_pris[0] = 1;
        }
        else if (choix == 2){
            strcpy(tab_joueurs[i].nomJoueur, "Tauriel");
            tab_joueurs[i].arme_a_trouver = ARC_M; 
            deja_pris[1] = 1;
        }
        else if (choix == 3){
            strcpy(tab_joueurs[i].nomJoueur, "Gollum");
            tab_joueurs[i].arme_a_trouver = ANNEAU; 
            deja_pris[2] = 1;
        }
        else if (choix == 4){
            strcpy(tab_joueurs[i].nomJoueur, "Gimli");
            tab_joueurs[i].arme_a_trouver = HACHE; 
            deja_pris[3] = 1;
        }
        printf("-> %s rejoint la quete !\n", tab_joueurs[i].nomJoueur);
    }
}
