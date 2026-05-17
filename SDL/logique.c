#include "memo_rpg.h"

Personnage* choix_arme(Personnage *x){ //Fonction qui demande a lutilisateur avant davancer quelle arme il veut chosir
    int armechoisie;
    do {
    printf("Quelle arme choississez vous ?\n");
    printf("1 -> ARC\n2 -> EPEE\n3 -> BDF\n4 -> LANCE\n");
    scanf("%d",&armechoisie);
    }while(armechoisie<1 || armechoisie>4);
    x->arme_actuelle = armechoisie - 1;
    return x;
}

int verifcaselibre(Plateau* tab, int colonne_new, int ligne_new){
    if (ligne_new < 1 || ligne_new > 5) {
        return 0; // Sortie tableau
    }
    if (colonne_new < 1 || colonne_new > 5) {
        return 0; // Sortie tableau
    }
    if(tab->tableau[ligne_new][colonne_new].est_decouverte == 1){
        return 0; 
    }
    return 1; 
}

int deplacement(Personnage* x, Plateau* tab) {
    int choixdeplacement;
    int deplacement_valide = 0; 
    // On vérifie les 4 directions. Si verifcaselibre renvoie 0 partout, le joueur est bloqué.
    if (verifcaselibre(tab, x->colonne, x->ligne - 1) == 0 && verifcaselibre(tab, x->colonne, x->ligne + 1) == 0 && verifcaselibre(tab, x->colonne + 1, x->ligne) == 0 && verifcaselibre(tab, x->colonne - 1, x->ligne) == 0) {
        printf("\n[BLOQUE] %s n'a plus de cases cachees accessibles autour de lui !\n", x->nomJoueur);
        reset_tableau(x, tab); // Retour à la position initiale
        return 1; // Signale la fin du tour pour sortir de la boucle de jeu
    }
    do {
        do {
            printf("\nOu voulez-vous aller ?\n");
            printf("1 -> Haut\n2 -> Bas\n3 -> Droite\n4 -> Gauche\n");
            printf("Choix : ");
            scanf("%d", &choixdeplacement);
            
            if (choixdeplacement > 4 || choixdeplacement < 1) {
                printf("Choix invalide. Tapez 1, 2, 3 ou 4.\n");
            }
        } while(choixdeplacement > 4 || choixdeplacement < 1);
        
        // Application de la direction choisie
        if (choixdeplacement == 1) { // HAUT
            if (verifcaselibre(tab, x->colonne, x->ligne - 1) == 1) {
                x->ligne = x->ligne - 1;
                deplacement_valide = 1; 
            } else {
                printf("Action impossible : case deja revelee ou hors limites.\n");
            }
        }
        else if (choixdeplacement == 2) { // BAS
            if (verifcaselibre(tab, x->colonne, x->ligne + 1) == 1) {
                x->ligne = x->ligne + 1;
                deplacement_valide = 1;
            } else {
                printf("Action impossible : case deja revelee ou hors limites.\n");
            }
        }
        else if (choixdeplacement == 3) { // DROITE
            if (verifcaselibre(tab, x->colonne + 1, x->ligne) == 1) {
                x->colonne = x->colonne + 1;
                deplacement_valide = 1;
            } else {
                printf("Action impossible : case deja revelee ou hors limites.\n");
            }
        }
        else if (choixdeplacement == 4) { // GAUCHE
            if (verifcaselibre(tab, x->colonne - 1, x->ligne) == 1) {
                x->colonne = x->colonne - 1;
                deplacement_valide = 1;
            } else {
                printf("Action impossible : case deja revelee ou hors limites.\n");
            }
        }

        // Si le déplacement a été validé par verifcaselibre, on révèle la case
        if (deplacement_valide == 1) {
            printf("Deplacement valide !\n");
            tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
        }

    } while (deplacement_valide == 0);

    return 0; // Le joueur a pu bouger normalement
}

void reset_tableau(Personnage* x, Plateau* tab) {
    // On cache le labyrinthe central 
    for (int i = 0; i < TAILLE; i++) { 
        for (int j = 0; j < TAILLE; j++) { 
            // Si on n'est PAS sur une des 4 cases de spawn, on cache
            if (!((i == 0 && j == 3) || (i == 3 && j == 0) || (i == 6 && j == 3) || (i == 3 && j == 6))) {
                tab->tableau[i][j].est_decouverte = 0; 
            } else {
                tab->tableau[i][j].est_decouverte = 1; // Le spawn reste visible
            }
        }
    }
    // 2. Positions exactes sous forme de croix 
    if (x->perso == GANDALF) {
        x->ligne = 0; x->colonne = 3;
    }
    else if (x->perso == TAURIEL) {
        x->ligne = 3; x->colonne = 6;
    }
    else if (x->perso == GOLLUM) {
        x->ligne = 3; x->colonne = 0;
    }
    else if (x->perso == GIMLI) {
        x->ligne = 6; x->colonne = 3;
    }
    printf("\n[DEFAITE] Le labyrinthe se referme... %s revient au point de depart !\n", x->nomJoueur);
}

int resolution_case(Personnage* x, Plateau* tab, int cible_ligne, int cible_colonne){ 
    Type_case case_actuelle = tab->tableau[x->ligne][x->colonne].type;
    int mort = 0; 
    
    // 1. Traduction du nom du personnage actuel
    char nom_du_perso[20];
    if (x->perso == GANDALF) {
        strcpy(nom_du_perso, "Gandalf"); // CORRECTION ICI !
    }
    else if (x->perso == TAURIEL) {
        strcpy(nom_du_perso, "Tauriel");
    }
    else if (x->perso == GOLLUM) {
        strcpy(nom_du_perso, "Gollum");
    }
    else if (x->perso == GIMLI) {
        strcpy(nom_du_perso, "Gimli");
    }

    if(case_actuelle == DRAGON){
        printf("\nUn DRAGON bloque la route ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == ARC){
            printf("SUCCESS : Le monstre est vaincu par votre ARC !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, le DRAGON vous a battu...\n");
            reset_tableau(x,tab);
            return 1; 
        }
    }
    
    if(case_actuelle == ORC){
        printf("\nUn ORC surgit des ombres ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == EPEE){
            printf("SUCCESS : Le monstre est vaincu par votre EPEE !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, l'ORC vous a battu...\n");
            reset_tableau(x,tab);
            return 1; 
        }
    }
    
    if(case_actuelle == NAZGUL){
        printf("\nUn NAZGUL fond sur vous ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == BDF){
            printf("SUCCESS : Le monstre est vaincu par votre BOULE DE FEU !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, le NAZGUL vous a battu...\n");
            reset_tableau(x,tab);
            return 1; 
        }
    }
    
    if(case_actuelle == ARAIGNEE){
        printf("\nUne ARAIGNEE GEANTE vous barre le chemin ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == LANCE){
            printf("SUCCESS : Le monstre est vaincu par votre LANCE !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, l'ARAIGNEE vous a battu...\n");
            reset_tableau(x,tab);
            return 1; 
        }
    }
    
    if(case_actuelle == ARME_SPE){
        int vrai_proprio = tab->tableau[x->ligne][x->colonne].proprietaire;
        
        if(vrai_proprio == (int)x->perso){
            printf("\nGenial ! %s (%s), vous avez trouve votre Arme de quete !\n", x->nomJoueur, nom_du_perso);
            x->aLarme = 1;
        }else{
            // CORRECTION ICI : On traduit le numéro du vrai proprio en texte !
            char nom_vrai_proprio[20];
            if (vrai_proprio == GANDALF) strcpy(nom_vrai_proprio, "Gandalf");
            else if (vrai_proprio == TAURIEL) strcpy(nom_vrai_proprio, "Tauriel");
            else if (vrai_proprio == GOLLUM) strcpy(nom_vrai_proprio, "Gollum");
            else if (vrai_proprio == GIMLI) strcpy(nom_vrai_proprio, "Gimli");
            
            printf("\nVous trouvez une arme au sol... mais ce n'est pas la votre, c'est celle de %s !\n", nom_vrai_proprio);
        }
    }
    
    if(case_actuelle == TRESOR){
        if(x->aLeTresor==0){
            printf("\nINCROYABLE ! %s (%s), vous avez trouve le Tresor !\n", x->nomJoueur, nom_du_perso);
            x->aLeTresor = 1;
        } else {
            printf("Vous avez deja un Tresor %s (%s)\n", x->nomJoueur, nom_du_perso);
        }
    }
    
    if(case_actuelle == TOTEM){
        printf("\nVous etes tombe sur un Totem ! La magie opère...\n");
        Type_case temp_type = tab->tableau[cible_ligne][cible_colonne].type;
        int temp_proprio = tab->tableau[cible_ligne][cible_colonne].proprietaire;
        tab->tableau[cible_ligne][cible_colonne].type = tab->tableau[x->ligne][x->colonne].type;
        tab->tableau[cible_ligne][cible_colonne].proprietaire = tab->tableau[x->ligne][x->colonne].proprietaire;
        tab->tableau[x->ligne][x->colonne].type = temp_type;
        tab->tableau[x->ligne][x->colonne].proprietaire = temp_proprio;
        printf("Les cases ont ete permutees !\n");
        mort = resolution_case(x, tab, 0, 0); // On résout la nouvelle case apparue !
        return mort;
    }
    
    if(case_actuelle == PORTAIL){
        printf("\nUn portail de teleportation ! Vouuuuh ! Teleportation en [%d][%d] !\n", cible_ligne, cible_colonne);
        x->ligne = cible_ligne;
        x->colonne = cible_colonne;
        tab->tableau[x->ligne][x->colonne].est_decouverte = 1; 
        mort = resolution_case(x, tab, 0, 0); // 
        return mort; 
    }
    
    return 0; // Reussit
}


void afficher_plateau(Plateau* tab, Personnage tab_joueurs[], int nb_joueurs) {
    printf("\n      --- PLATEAU DE JEU 7x7 ---\n\n");
    printf("    0   1   2   3   4   5   6\n");
    printf("  +---+---+---+---+---+---+---+\n");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d |", i); //print les colonnes
        for (int j = 0; j < TAILLE; j++) {
            int joueur_present = -1;
            for (int k = 0; k < nb_joueurs; k++) {
                if (tab_joueurs[k].ligne == i && tab_joueurs[k].colonne == j) {
                    joueur_present = k;
                    break;
                }
            }
            if (joueur_present != -1) {
                printf(" J%d|", joueur_present + 1);
            } 
            else if (tab->tableau[i][j].type == VIDE) {
                printf("   |"); // Les coins sont vides
            } 
            else {
                Type_case t = tab->tableau[i][j].type;
                if (t == DRAGON) printf(" D |");
                else if (t == ORC) printf(" O |");
                else if (t == NAZGUL) printf(" N |");
                else if (t == ARAIGNEE) printf(" A |");
                else if (t == TRESOR) printf(" T |");
                else if (t == ARME_SPE) printf(" W |");
                else if (t == PORTAIL) printf(" P |");
                else if (t == TOTEM) printf(" M |");
                else if (t == DEPART) printf(" S |");
                else printf("   |");
            }
        }
        printf("\n  +---+---+---+---+---+---+---+\n");
    }
}

void deroulement_jeu(Plateau* tab, Personnage* joueur, int nb_joueurs){ 
    int fin_de_partie = 0;
    int morts_partie[4] = {0, 0, 0, 0};

    while(fin_de_partie == 0){
        for(int i = 0; i < nb_joueurs; i++){
            int mort = 0; // Le joueur commence son tour bien vivant
            // Tant que le joueur est en vie et que la partie n'est pas finie, il rejoue !
            while(mort == 0 && fin_de_partie == 0) {
                afficher_plateau(tab, joueur, nb_joueurs);
                printf("\n=============================\n");
                printf(" C'est à %s de jouer\n", joueur[i].nomJoueur);
                printf("=============================\n");
                
                deplacement(&joueur[i], tab);
                choix_arme(&joueur[i]);
                
                // On récupère 1 si mort, 0 si vivant
                mort = resolution_case(&joueur[i], tab, 0, 0);

                if (mort == 1) {
                    morts_partie[i]++; 
                }
                
                if(joueur[i].aLeTresor == 1 && joueur[i].aLarme == 1){
                    printf("\n!!! VICTOIRE !!! %s a gagne la partie !\n", joueur[i].nomJoueur);
                    //vainqueur
                    mettre_a_jour_stats(joueur[i].nomJoueur, 1, 0, morts_partie[i]);

                    //perdant
                    for (int k = 0; k < nb_joueurs; k++) {
                        if (k != i) {
                            mettre_a_jour_stats(joueur[k].nomJoueur, 0, 1, morts_partie[k]);
                        }
                    }
                    fin_de_partie = 1;
                    break;
                }
            }
            // Quand "mort" passe à 1, la boucle s'arrête et on passe au joueur suivant
        }
    }
}


