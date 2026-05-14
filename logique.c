#include "memo_rpg.h"

Personnage* choix_arme(Personnage *x){ //Fonction qui demande a lutilisateur avant davancer quelle arme il veut chosir
    int armechoisie;
    int verif;
    do {
    printf("Quelle arme choississez vous ?\n");
    printf("1 -> ARC\n2 -> EPEE\n3 -> BDF\n4 -> LANCE\n");
    verif=scanf("%d",&armechoisie);
    vide_buffer();
    }while(armechoisie<1 || armechoisie>4 || verif!=1);
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
    int verif;
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
            verif=scanf("%d", &choixdeplacement);
            
            if (choixdeplacement > 4 || choixdeplacement < 1) {
                printf("Choix invalide. Tapez 1, 2, 3 ou 4.\n");
            }
            vide_buffer();
        } while(choixdeplacement > 4 || choixdeplacement < 1 || verif!=1);
        
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
    x->aLarme = 0;
    x->aLeTresor = 0;
    
    printf("\n[DEFAITE] Le labyrinthe se referme... %s revient au point de depart !\n", x->nomJoueur);
}

int resolution_case(Personnage* x, Plateau* tab){ 
    Type_case case_actuelle = tab->tableau[x->ligne][x->colonne].type;
    int mort = 0; // Variable pour retenir si on meurt dans un portail
    int verif;
    
    // On vérifie le type de case et on regarde si le joeuur a la bonne arme 
    if(case_actuelle == DRAGON){
        printf("\nUn DRAGON bloque la route ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == ARC){
            printf("SUCCESS : Le monstre est vaincu par votre ARC !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, le DRAGON vous a battu...\n");
            reset_tableau(x,tab);
            return 1; // On signale la mort
        }
    }
    
    if(case_actuelle == ORC){
        printf("\nUn ORC surgit des ombres ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == EPEE){
            printf("SUCCESS : Le monstre est vaincu par votre EPEE !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, l'ORC vous a battu...\n");
            reset_tableau(x,tab);
            return 1; // <--- AJOUT : On signale la mort
        }
    }
    
    if(case_actuelle == NAZGUL){
        printf("\nUn NAZGUL fond sur vous ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == BDF){
            printf("SUCCESS : Le monstre est vaincu par votre BOULE DE FEU !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, le NAZGUL vous a battu...\n");
            reset_tableau(x,tab);
            return 1; // <--- AJOUT : On signale la mort
        }
    }
    
    if(case_actuelle == ARAIGNEE){
        printf("\nUne ARAIGNEE GEANTE vous barre le chemin ! Preparez-vous au combat.\n");
        if(x->arme_actuelle == LANCE){
            printf("SUCCESS : Le monstre est vaincu par votre LANCE !\n");
        }else{
            printf("DEFAITE : Vous aviez la mauvaise arme, l'ARAIGNEE vous a battu...\n");
            reset_tableau(x,tab);
            return 1; // <--- AJOUT : On signale la mort
        }
    }
    
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
    
    if(case_actuelle == TOTEM){
        int colonne, ligne;
        printf("\nVous etes tombe sur un Totem ! La magie va operer...\n");
        // 1. Demander la case cible (doit être cachée)
        do {
            printf("Entrez la ligne puis la colonne d'une case CACHEE pour l'echanger : ");
            verif=scanf("%d %d", &ligne, &colonne);
            if(ligne < 1 || ligne > 5 || colonne < 1 || colonne > 5 || tab->tableau[ligne][colonne].est_decouverte == 1) {
                printf("Cible invalide ! Choisissez une case dans le labyrinthe qui n'est pas encore revelee.\n");
            }
            vide_buffer();
        } while(ligne < 1 || ligne > 5 || colonne < 1 || colonne > 5 || tab->tableau[ligne][colonne].est_decouverte == 1 || verif!=2); 
        // 2. Échanger les types de cases 
        Type_case temp = tab->tableau[ligne][colonne].type;
        tab->tableau[ligne][colonne].type = tab->tableau[x->ligne][x->colonne].type;
        tab->tableau[x->ligne][x->colonne].type = temp;
        printf("Les cases ont ete permutees ! La magie du Totem vous epuise...\n");
        reset_tableau(x, tab); 
        return 1; // Signale la fin du tour (comme une mort) pour sortir de la boucle rejouer
    }
    
    if(case_actuelle == PORTAIL){
        int colonne, ligne;
        printf("\nUn portail de teleportation ! Ou voulez-vous apparaitre ?\n");
        do{
            printf("Entrez la ligne puis la colonne : ");
            verif=scanf("%d %d", &ligne, &colonne);
            if(ligne < 1 || ligne > 5 || colonne < 1 || colonne > 5){
                printf("Erreur, case en dehors du plateau de jeu\n");
            }
            vide_buffer();
        } while(ligne < 1 || ligne > 5 || colonne < 1 || colonne > 5 || verif!=2);
        x->ligne = ligne;
        x->colonne = colonne;
        tab->tableau[x->ligne][x->colonne].est_decouverte = 1; 
        printf("Vouuuuh ! Teleportation en [%d][%d] !\n", ligne, colonne);
        mort = resolution_case(x, tab); // ca renvoit 1 si le mec est mort ou 0 si il a reussit
        return mort; 
        }
    return 0; // Reussit
    }

void afficher_plateau(Plateau* tab, Personnage tab_joueurs[], int nb_joueurs) {
    printf("\n      --- PLATEAU DE JEU 7x7 ---\n\n");
    couleur("30"); //Numéros de colonnes en gris
    printf("    0   1   2   3   4   5   6\n");
    couleur("8");
    printf("  +---+---+---+---+---+---+---+\n"); // A CACHER
    couleur("0");
    for (int i = 0; i < TAILLE; i++) {
        couleur("30"); //Numéros de lignes en gris
        printf("%d ", i); //print les colonnes
        couleur("8");
        printf("|"); //A CACHER
        couleur("0");
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
                couleur("8");
                if(j==0 && i<TAILLE-1 && i>0) couleur("0");
                if(j==TAILLE/2-1 && (i==0 ||i==TAILLE-1)) couleur("0");
                printf("   |"); // Les coins sont vides
                couleur("0");
            } 
            else {
                Type_case t = tab->tableau[i][j].type;
                couleur("31"); //Rouge
                if (t == DRAGON) printf(" D ");
                else if (t == ORC) printf(" O ");
                else if (t == NAZGUL) printf(" N ");
                else if (t == ARAIGNEE) printf(" A ");
                
                else if (t == TRESOR){
                    couleur("33");
                    printf(" T ");}
                else if (t == ARME_SPE){
                    couleur("34"); //Bleu
                    printf(" W ");}
                else if (t == PORTAIL){
                    couleur("35"); //Violet
                    printf(" P ");}
                else if (t == TOTEM){
                    couleur("36");
                    printf(" M ");}
                else if (t == DEPART){
                    couleur("0");
                    printf(" S ");}
                else printf("   ");
                couleur("0");
                if(j==TAILLE-1 && i==(TAILLE-1)/2) couleur("8");
                printf("|");
                couleur("0");
            }
        }
        if(i<2 || i>3 ) couleur("8");
        printf("\n  ----");//A CACHER
        if(i!=6) couleur("0"); //dernière ligne
        printf("+---+---+---+---+---+");
        if(i<2 || i>3 ) couleur("8");
        printf("----\n"); //A CACHER
        couleur("0");
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
                mort = resolution_case(&joueur[i], tab);

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


