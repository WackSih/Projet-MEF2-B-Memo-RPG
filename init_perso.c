#include"memo_rpg.h"

void depart(Personnage tab_joueurs[], int nb_joueurs) { //Initialise la position des perso sur la map en fct du nb de joueurs
    for (int i = 0; i < nb_joueurs; i++) {
        tab_joueurs[i].aLarme = 0;
        tab_joueurs[i].aLeTresor = 0;
        tab_joueurs[i].arme_actuelle = EPEE; // Arme par défaut

        if (i == 0) { // Nord
            tab_joueurs[i].ligne = -1; 
            tab_joueurs[i].colonne = 2;
        }
        else if (i == 1) { 
            if (nb_joueurs == 2) { // Face à face si il y a que 2 joueurs
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
            tab_joueurs[i].colonne = -1;
        }
    }
}

void select_perso(Personnage tab_joueurs[], int nb_joueurs) {
    int choix = 0;
	int deja_pris[4] = {0, 0, 0, 0};
    for (int i = 0; i < nb_joueurs; i++) {
        printf("\nJoueur %d, choisissez votre personnage :\n", i + 1);
        printf("1: GANDALF\n2: TAURIEL\n3: GOLLUM\n4: GIMLI\nChoix : ");
        do {
            scanf("%d", &choix);
            if (choix < 1 || choix > 4 || deja_pris[choix-1] == 1) {
                printf("Choix invalide ou deja pris, recommencez :\n ");
            }
        } while(choix < 1 || choix > 4 || deja_pris[choix-1] == 1);

        tab_joueurs[i].perso = (Classe)(choix-1); //Mise à jour de la structure des joueurs
        
        if (choix == 1){ 
			strcpy(tab_joueurs[i].nomJoueur, "Gandalf");
			tab_joueurs[i].arme_a_trouver = BATON; // ARME_SPE de Gandalf
			deja_pris[0] = 1;}
        else if (choix == 2){
			strcpy(tab_joueurs[i].nomJoueur, "Tauriel");
			tab_joueurs[i].arme_a_trouver = ARC_M; // ARME_SPE de Tauriel
			deja_pris[1] = 1;}
        else if (choix == 3){
			strcpy(tab_joueurs[i].nomJoueur, "Gollum");
			tab_joueurs[i].arme_a_trouver = ANNEAU; // ARME_SPE de Gollum
			deja_pris[2] = 1;}
        else if (choix == 4){
			strcpy(tab_joueurs[i].nomJoueur, "Gimli");
			tab_joueurs[i].arme_a_trouver = HACHE; // ARME_SPE de Gimli
			deja_pris[3] = 1;}
    }