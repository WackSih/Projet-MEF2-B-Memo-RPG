#include "memo_rpg.h"

void depart(Personnage tab_joueurs[], int nb_joueurs) { 
    for (int i = 0; i < nb_joueurs; i++) {
        // Initialisation de base
        tab_joueurs[i].aLarme = 0;
        tab_joueurs[i].aLeTresor = 0;
        tab_joueurs[i].arme_actuelle = EPEE;
        if (tab_joueurs[i].perso == GANDALF) { //(Nord)
            tab_joueurs[i].ligne = 0;       //En Haut
            tab_joueurs[i].colonne = 3;     //Au milieu
        }
        else if (tab_joueurs[i].perso == TAURIEL) { //(Est/
            tab_joueurs[i].ligne = 3;       //Au Centre
            tab_joueurs[i].colonne = 6;     //A Droite
        }
        else if (tab_joueurs[i].perso == GOLLUM) { //(Ouest)
            tab_joueurs[i].ligne = 3;       //Au Centre
            tab_joueurs[i].colonne = 0;     //A Gauche
        }
        else if (tab_joueurs[i].perso == GIMLI) { //(Sud)
            tab_joueurs[i].ligne = 6;       //En Bas
            tab_joueurs[i].colonne = 3;     //Au Milieu
        }
    }
}


void select_perso(Personnage tab_joueurs[], int nb_joueurs) {
    int choix;
    int deja_pris[4] = {0, 0, 0, 0}; // 0 = libre, 1 = pris
    for (int i = 0; i < nb_joueurs; i++) {
        do {
            printf("\nJoueur %d, choisissez votre personnage :\n 1 - Gandalf\n 2 - Tauriel \n 3 - Gollum \n 4 - Gimli : ", i + 1);
            scanf("%d", &choix);
            if (choix < 1 || choix > 4) {
                printf("Choix invalide !\n");
            } else if (deja_pris[choix - 1] == 1) {
                printf("Ce personnage est deja pris, choisissez-en un autre !\n");
            }
        } while (choix < 1 || choix > 4 || deja_pris[choix - 1] == 1);
        deja_pris[choix - 1] = 1; // On marque comme pris
        tab_joueurs[i].perso = (Classe)(choix - 1);
        printf("Joueur %d, quel est votre pseudo ? ", i + 1);
        scanf("%s", tab_joueurs[i].nomJoueur);
        // Attribution de l'arme antique (on garde tes noms)
        if (choix == 1) tab_joueurs[i].arme_a_trouver = BATON;
        else if (choix == 2) tab_joueurs[i].arme_a_trouver = ARC_M;
        else if (choix == 3) tab_joueurs[i].arme_a_trouver = ANNEAU;
        else if (choix == 4) tab_joueurs[i].arme_a_trouver = HACHE;
        printf("Joueur %d (%s) a choisi la classe %d\n", i + 1, tab_joueurs[i].nomJoueur, choix);
    }
}

