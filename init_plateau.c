#include "memo_rpg.h"

Plateau initialisation(Personnage tab_joueurs[], int nb_joueur) {
    Plateau p;
    Case liste[25]; 
    int i, compteur = 0;

    // OBJETS FIXES ET MONSTRES DE BASE (18 cases)
    for(i = 0; i < 4; i++) { liste[compteur].type = DRAGON; liste[compteur].proprietaire = -1; compteur++; }
    for(i = 0; i < 4; i++) { liste[compteur].type = ORC; liste[compteur].proprietaire = -1; compteur++; }
    for(i = 0; i < 4; i++) { liste[compteur].type = NAZGUL; liste[compteur].proprietaire = -1; compteur++; }
    for(i = 0; i < 4; i++) { liste[compteur].type = ARAIGNEE; liste[compteur].proprietaire = -1; compteur++; }
    liste[compteur].type = TRESOR; liste[compteur].proprietaire = -1; compteur++;
    liste[compteur].type = TRESOR; liste[compteur].proprietaire = -1; compteur++;
    liste[compteur].type = TOTEM; liste[compteur].proprietaire = -1; compteur++;
    liste[compteur].type = TOTEM; liste[compteur].proprietaire = -1; compteur++;
    liste[compteur].type = PORTAIL; liste[compteur].proprietaire = -1; compteur++;

    //ARMES SPÉCIFIQUES (Seulement pour les joueurs présents)
    for(i = 0; i < nb_joueur; i++) {
        liste[compteur].type = ARME_SPE;
        if (tab_joueurs[i].perso == GANDALF) {
            liste[compteur].proprietaire = 0;
        } 
        else if (tab_joueurs[i].perso == TAURIEL) {
            liste[compteur].proprietaire = 1;
        } 
        else if (tab_joueurs[i].perso == GOLLUM) {
            liste[compteur].proprietaire = 2;
        } 
        else if (tab_joueurs[i].perso == GIMLI) {
            liste[compteur].proprietaire = 3;
        } // On lie l'arme au perso
        compteur++;
    }

    // REMPLISSAGE DU RESTE AVEC DES MONSTRES
    // S'il manque des cases pour arriver à 25 (ex: partie à 2 ou 3 joueurs)
    while(compteur < 25) {
        int monstre_aleatoire = rand() % 4; // Tire un chiffre entre 0 et 3
        
        if (monstre_aleatoire == 0) liste[compteur].type = DRAGON;
        else if (monstre_aleatoire == 1) liste[compteur].type = ORC;
        else if (monstre_aleatoire == 2) liste[compteur].type = NAZGUL;
        else liste[compteur].type = ARAIGNEE;
        liste[compteur].proprietaire = -1;
        compteur++;
    }

    // Mélange Parfait Fisher-Yates
    for(i = 0; i < 25; i++){
        liste[i].est_decouverte = 0;
    }
    for(i = 24; i > 0; i--) {
        int j = rand() % (i + 1);
        Case temp = liste[i];
        liste[i] = liste[j];
        liste[j] = temp;
    }

    int index_liste = 0;
    for(int lig = 0; lig < TAILLE; lig++) {
        for(int col = 0; col < TAILLE; col++) {
            // Carré central
            if (lig >= 1 && lig <= 5 && col >= 1 && col <= 5) {
                p.tableau[lig][col] = liste[index_liste++];
            } 
            // Spawn joueurs
            else if ((lig == 0 && col == 3) || (lig == 3 && col == 0) || 
                     (lig == 6 && col == 3) || (lig == 3 && col == 6)) {
                p.tableau[lig][col].type = DEPART; // Laisse ça en PORTAIL ou VIDE, c'est juste le visuel du spawn
                p.tableau[lig][col].est_decouverte = 1;
                p.tableau[lig][col].proprietaire = -1;
            } 
            // Bords inutilisés
            else {
                p.tableau[lig][col].type = VIDE;
                p.tableau[lig][col].est_decouverte = 1;
                p.tableau[lig][col].proprietaire = -1;
            }
        }
    }
    return p;
}

