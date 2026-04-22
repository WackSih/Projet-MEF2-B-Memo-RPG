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

void reset_tableau(Personnage* x, Plateau* tab) {
    for (int i = 0; i < 5; i++) { 
        for (int j = 0; j < 5; j++) { 
            tab->tableau[i][j].est_decouverte = 0; 
        }
    }
    // RESET ICI (attente coordonnes depart)
    printf("Le labyrinthe se referme... Retour a la case depart !\n");
}

void resolution_case(Personnage* x, Plateau* tab){ //FOnction qui va faire laction de la case
    Type_case case_actuelle = tab->tableau[x->ligne][x->colonne].type;
    if(case_actuelle == DRAGON){
        if(x->arme_actuelle == ARC){
            printf("Le monstre est vaincu\n");
        }else{
            printf("Vous aviez la mauvaise arme, dommage vous etes mort\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == ORC){
        if(x->arme_actuelle == EPEE){
            printf("Le monstre est vaincu\n");
        }else{
            printf("Vous aviez la mauvaise arme, dommage vous etes mort\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == NAZGUL){
        if(x->arme_actuelle == BDF){
            printf("Le monstre est vaincu\n");
        }else{
            printf("Vous aviez la mauvaise arme, dommage vous etes mort\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == ARAIGNE){
        if(x->arme_actuelle == LANCE){
            printf("Le monstre est vaincu\n");
        }else{
            printf("Vous aviez la mauvaise arme, dommage vous etes mort\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == HACHE){
        if(x->perso == GIMLI){
            printf("Vous avez trouvé votre Arme\n");
            x->aLarme = 1;
        }else{
            printf("Ce n'est pas votre trésor\n");
        }
    }
    if(case_actuelle == ANNEAU){
        if(x->perso == GOLLUM){
            printf("Vous avez trouvé votre Arme\n");
            x->aLarme = 1;
        }else{
            printf("Ce n'est pas votre trésor\n");
        }
    }
    if(case_actuelle == ARC_M){
        if(x->perso == TAURIEL){
            printf("Vous avez trouvé votre Arme\n");
            x->aLarme = 1;
        }else{
            printf("Ce n'est pas votre trésor\n");
        }
    }
    if(case_actuelle == BATON){
        if(x->perso == GANDALF){
            printf("Vous avez trouvé votre Arme\n");
            x->aLarme = 1;
        }else{
            printf("Ce n'est pas votre trésor\n");
        }
    }
    if(case_actuelle == TRESOR){
        printf("Vous avez trouvé le Trésor !\n");
        x->aLeTresor = 1;
    }
    if(case_actuelle == TOTEM){
        int colonne, ligne;
        do{
            printf("Vous etes tombe sur un Totem\n");
            printf("Entrez la ligne puis la colonne de la case CACHEE que vous voulez echanger\n");
            scanf("%d %d", &ligne, &colonne);
        } while(ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4 || tab->tableau[ligne][colonne].est_decouverte == 1); 
        Type_case temp = tab->tableau[ligne][colonne].type;
        tab->tableau[ligne][colonne].type = tab->tableau[x->ligne][x->colonne].type;
        tab->tableau[x->ligne][x->colonne].type = temp;
    }
    if(case_actuelle == PORTAIL){
        int colonne, ligne;
        do{
            printf("Vous etes tombe sur un portail de teleportation\n");
            printf("Choississez la case ou vous voulez vous teleporter\n");
            scanf("%d %d", &ligne, &colonne);
        } while(ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4); 
        x->ligne = ligne;
        x->colonne = colonne;
        tab->tableau[x->ligne][x->colonne].est_decouverte = 1; 
        printf("Vous vous etes teleporte en [%d][%d] !\n", ligne, colonne);
        resolution_case(x, tab); 
    }

void deroulement_jeu(Plateau* tab, Personnage* joueur, int nb_joueurs){ //ATTENTION TABLEAU DE JOUEUR ICI
    int fin_de_partie = 0;
    while(fin_de_partie==0){
        for(int i=0;i<nb_joueurs;i++){
            printf("Cest au joueurs numéro %d de jouer\n",i+1);
            deplacement(joueur[i],tab);
            choix_arme(joueur[i],tab);
            resolution_case(&joueur[i],tab);
            if(joueur[i]->aLeTresor==1 && joueur[i]->aLarme==1){
                printf("Le joueur numéro %d a gagné\n",i+1);
                fin_de_partie=1;
                break;
            }
        }
    }
}
