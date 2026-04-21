#include "memo_rpg.h"

Personnage* choix_arme(Personnage *x){ //Fonction qui demande a lutilisateur avant davancer quelle arme il veut chosir
    int armechoisie;
    do {
    printf("Quelle arme choississez vous ?\n");
    printf("1 -> ARC\n 2 -> EPEE\n 3 -> BDF\n 4 -> LANCE\n");
    scanf("%d",&armechoisie);
    }while(armechoisie<1 || armechoisie>4);
    x->arme_actuelle = armechoisie - 1;
    return x;
}

int verifcaselibre(Plateau* tab, int colonne_new, int ligne_new){
    if (ligne_new < 0 || ligne_new > 4) {
        return 0; //Sortie tableau
    }
    if (colonne_new < 0 || colonne_new > 4) {
        return 0; //Sortie tableau
    }
    if(tab->tableau[ligne_new][colonne_new].est_decouverte == 1){
        return 0; //Case deja decouverte il peut pas retourner dessus
    }
    return 1; //Toutes les conditions sont bonnes il peut aller sur la case

}

void deplacement(Personnage* x, Plateau* tab){ //FOnction qui permet de faire les deplacements
    int choixdeplacement;
    int deplacement_valide = 0; 
    do {
        do{
        printf("Ou voulez vous aller ?\n");
        printf("1 -> Haut\n 2 -> Bas\n 3 -> Droite\n 4 -> Gauche\n");
        scanf("%d", &choixdeplacement);
        if (choixdeplacement > 4 || choixdeplacement < 1) {
            printf("Choix invalide. Tapez 1, 2, 3 ou 4.\n");
        }
        }while(choixdeplacement > 4 || choixdeplacement < 1);
        if (choixdeplacement == 1) {
            if (verifcaselibre(tab, x->colonne, x->ligne - 1) == 1) {
                printf("Déplacement valide\n");
                x->ligne = x->ligne - 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1; 
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
        else if (choixdeplacement == 2) {
            if (verifcaselibre(tab, x->colonne, x->ligne + 1) == 1) {
                printf("Déplacement valide\n");
                x->ligne = x->ligne + 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1;
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
        else if (choixdeplacement == 3) {
            if (verifcaselibre(tab, x->colonne + 1, x->ligne) == 1) {
                printf("Déplacement valide\n");
                x->colonne = x->colonne + 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1;
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
        else if (choixdeplacement == 4) {
            if (verifcaselibre(tab, x->colonne - 1, x->ligne) == 1) {
                printf("Déplacement valide\n");
                x->colonne = x->colonne - 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1;
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
    } while (deplacement_valide == 0);
}