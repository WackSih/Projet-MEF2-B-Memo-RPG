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
    // Bornes passées à 6 pour le plateau 7x7 (indices 0 à 6)
    if (ligne_new < 0 || ligne_new > 6) {
        return 0; // Sortie tableau
    }
    if (colonne_new < 0 || colonne_new > 6) {
        return 0; // Sortie tableau
    }
    
    // Ta condition : on ne peut pas marcher sur une case déjà révélée
    if(tab->tableau[ligne_new][colonne_new].est_decouverte == 1){
        return 0; 
    }
    
    return 1; // Le déplacement est autorisé
}

void deplacement(Personnage* x, Plateau* tab){ // Ta fonction originale
    int choixdeplacement;
    int deplacement_valide = 0; 
    do {
        do {
            printf("Ou voulez vous aller ?\n");
            printf("1 -> Haut\n 2 -> Bas\n 3 -> Droite\n 4 -> Gauche\n");
            scanf("%d", &choixdeplacement);
            if (choixdeplacement > 4 || choixdeplacement < 1) {
                printf("Choix invalide. Tapez 1, 2, 3 ou 4.\n");
            }
        } while(choixdeplacement > 4 || choixdeplacement < 1);

        if (choixdeplacement == 1) { // HAUT
            // L'Arbitre vérifie si la case d'arrivée (ligne - 1) est valide
            if (verifcaselibre(tab, x->colonne, x->ligne - 1) == 1) {
                printf("Déplacement valide\n");
                x->ligne = x->ligne - 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1; 
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
        else if (choixdeplacement == 2) { // BAS
            if (verifcaselibre(tab, x->colonne, x->ligne + 1) == 1) {
                printf("Déplacement valide\n");
                x->ligne = x->ligne + 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1;
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
        else if (choixdeplacement == 3) { // DROITE
            if (verifcaselibre(tab, x->colonne + 1, x->ligne) == 1) {
                printf("Déplacement valide\n");
                x->colonne = x->colonne + 1;
                tab->tableau[x->ligne][x->colonne].est_decouverte = 1;
                deplacement_valide = 1;
            } else {
                printf("Erreur, choisissez un autre deplacement\n");
            }
        }
        else if (choixdeplacement == 4) { // GAUCHE
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
    // 1. On cache uniquement le labyrinthe central (indices 1 à 5)
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
    // 2. Positions exactes sur la croix (indices 0, 3, 6)
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
    x->aLarme = 0;
    x->aLeTresor = 0;
    mettre_a_jour_stats(x->nomJoueur, 0); // 0 = défaite
    printf("\n[DEFAITE] Le labyrinthe se referme... %s revient au point de depart !\n", x->nomJoueur);
}

void resolution_case(Personnage* x, Plateau* tab){ 
    Type_case case_actuelle = tab->tableau[x->ligne][x->colonne].type;

    // --- MONSTRES ---
    // On vérifie le type de case, on annonce le monstre, et SEULEMENT là on demande l'arme
    if(case_actuelle == DRAGON){
        printf("\nUn DRAGON bloque la route ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == ARC){
            printf("SUCCESS : Le monstre est vaincu par votre ARC !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, le DRAGON vous a battu...\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == ORC){
        printf("\nUn ORC surgit des ombres ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == EPEE){
            printf("SUCCESS : Le monstre est vaincu par votre EPEE !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, l'ORC vous a battu...\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == NAZGUL){
        printf("\nUn NAZGUL fond sur vous ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == BDF){
            printf("SUCCESS : Le monstre est vaincu par votre BOULE DE FEU !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, le NAZGUL vous a battu...\n");
            reset_tableau(x,tab);
        }
    }
    if(case_actuelle == ARAIGNEE || case_actuelle == ARAIGNE){
        printf("\nUne ARAIGNEE GEANTE vous barre le chemin ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == LANCE){
            printf("SUCCESS : Le monstre est vaincu par votre LANCE !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, l'ARAIGNEE vous a battu...\n");
            reset_tableau(x,tab);
        }
    }

    // --- OBJETS ET ARMES SPECIALES ---
    // Ici on garde ta logique de vérification par personnage
    if(case_actuelle == ARME_SPE){
        // On utilise le propriétaire défini à l'initialisation (0=Gandalf, 1=Tauriel, etc.)
        if(tab->tableau[x->ligne][x->colonne].proprietaire == (int)x->perso){
            printf("\nGenial ! %s, vous avez trouve votre Arme de quete !\n", x->nomJoueur);
            x->aLarme = 1;
        }else{
            printf("\nVous trouvez une arme au sol... mais ce n'est pas la votre.\n");
        }
    }

    if(case_actuelle == TRESOR){
        printf("\nINCROYABLE ! %s, vous avez trouve le Tresor !\n", x->nomJoueur);
        x->aLeTresor = 1;
    }

    // --- CASES SPECIALES ---
    if(case_actuelle == TOTEM){
        int colonne, ligne;
        printf("\nVous etes tombe sur un Totem ! La magie va operer...\n");
        do{
            printf("Entrez la ligne puis la colonne d'une case CACHEE pour l'echanger : ");
            scanf("%d %d", &ligne, &colonne);
        } while(ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4 || tab->tableau[ligne][colonne].est_decouverte == 1); 
        
        Type_case temp = tab->tableau[ligne][colonne].type;
        tab->tableau[ligne][colonne].type = tab->tableau[x->ligne][x->colonne].type;
        tab->tableau[x->ligne][x->colonne].type = temp;
        printf("Les cases ont ete permutees !\n");
    }

    if(case_actuelle == PORTAIL){
        int colonne, ligne;
        printf("\nUn portail de teleportation ! Ou voulez-vous apparaitre ?\n");
        do{
            printf("Entrez la ligne puis la colonne : ");
            scanf("%d %d", &ligne, &colonne);
        } while(ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4); 
        
        x->ligne = ligne;
        x->colonne = colonne;
        tab->tableau[x->ligne][x->colonne].est_decouverte = 1; 
        printf("Vouuuuh ! Teleportation en [%d][%d] !\n", ligne, colonne);
        resolution_case(x, tab); // On relance la logique sur la nouvelle case
    }
}

void afficher_plateau(Plateau* tab, Personnage tab_joueurs[], int nb_joueurs) {
    printf("\n      --- PLATEAU DE JEU 7x7 ---\n\n");
    
    // On affiche les indices de 0 à 6
    printf("    0   1   2   3   4   5   6\n");
    printf("  +---+---+---+---+---+---+---+\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("%d |", i); 
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
                // Affichage des symboles (D, O, N, A, etc.)
                Type_case t = tab->tableau[i][j].type;
                if (t == DRAGON) printf(" D |");
                else if (t == ORC) printf(" O |");
                else if (t == NAZGUL) printf(" N |");
                else if (t == ARAIGNEE || t == ARAIGNE) printf(" A |");
                else if (t == TRESOR) printf(" T |");
                else if (t == ARME_SPE) printf(" W |");
                else if (t == PORTAIL) printf(" P |");
                else if (t == TOTEM) printf(" M |");
                else printf("   |");
            }
        }
        printf("\n  +---+---+---+---+---+---+---+\n");
    }
}

void deroulement_jeu(Plateau* tab, Personnage* joueur, int nb_joueurs){ 
    int fin_de_partie = 0;
    while(fin_de_partie == 0){
        for(int i = 0; i < nb_joueurs; i++){
            afficher_plateau(tab, joueur, nb_joueurs);
            printf("C'est au joueur numero %d de jouer\n", i + 1);
            deplacement(&joueur[i], tab);
            choix_arme(&joueur[i]);
            resolution_case(&joueur[i], tab);
            if(joueur[i].aLeTresor == 1 && joueur[i].aLarme == 1){
                printf("Le joueur numero %d a gagne\n", i + 1);
                mettre_a_jour_stats(joueur[i].nomJoueur, 1); // 1 = victoire
                fin_de_partie = 1;
                break;
            }
        }
    }
}



