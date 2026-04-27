#include "memo_rpg.h"

/**
 * Initialise la position de départ des joueurs sur la bordure du plateau 6x6.
 * Les joueurs commencent sur des cases neutres pour éviter les monstres au spawn.
 */
void depart(Personnage tab_joueurs[], int nb_joueurs) { 
    for (int i = 0; i < nb_joueurs; i++) {
        // Initialisation de base
        tab_joueurs[i].aLarme = 0;
        tab_joueurs[i].aLeTresor = 0;
        tab_joueurs[i].arme_actuelle = EPEE;
        if (tab_joueurs[i].perso == GANDALF) {
            tab_joueurs[i].ligne = 0; 
            tab_joueurs[i].colonne = 3;
        }
        else if (tab_joueurs[i].perso == TAURIEL) {
            tab_joueurs[i].ligne = 3;
            tab_joueurs[i].colonne = 6;
        }
        else if (tab_joueurs[i].perso == GOLLUM) {
            tab_joueurs[i].ligne = 3;
            tab_joueurs[i].colonne = 0;
        }
        else if (tab_joueurs[i].perso == GIMLI) {
            tab_joueurs[i].ligne = 6;
            tab_joueurs[i].colonne = 3;
        }
    }
}

/**
 * Permet à chaque joueur de choisir un personnage unique.
 * Gère la duplication pour qu'un personnage ne soit pas choisi deux fois.
 */
void select_perso(Personnage tab_joueurs[], int nb_joueurs) {
    int choix;
    for (int i = 0; i < nb_joueurs; i++) {
        // On demande le choix au moins une fois
        printf("\nJoueur %d, choisissez votre personnage :\n 1 - Gandalf\n 2 - Tauriel \n 3 - Gollum \n 4 - Gimli  : \n", i + 1);
        scanf("%d", &choix); 

        // On simplifie : on enregistre direct
        tab_joueurs[i].perso = (Classe)(choix - 1); 

        if (choix == 1) {
            strcpy(tab_joueurs[i].nomJoueur, "Gandalf");
            tab_joueurs[i].arme_a_trouver = BATON;
        }
        else if (choix == 2) {
            strcpy(tab_joueurs[i].nomJoueur, "Tauriel");
            tab_joueurs[i].arme_a_trouver = ARC_M;
        }
        else if (choix == 3) {
            strcpy(tab_joueurs[i].nomJoueur, "Gollum");
            tab_joueurs[i].arme_a_trouver = ANNEAU;
        }
        else if (choix == 4) {
            strcpy(tab_joueurs[i].nomJoueur, "Gimli");
            tab_joueurs[i].arme_a_trouver = HACHE;
        }
        
        printf("Joueur %d a choisi %s\n", i + 1, tab_joueurs[i].nomJoueur);
    }
}
