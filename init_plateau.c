#include "memo_rpg.h"

Plateau initialisation() {
    Plateau p;
    // On crée une liste de 25 cases (5x5) pour le labyrinthe interactif
    Case liste[25]; 
    int i;
    int compteur = 0;

    // --- 1. REMPLISSAGE DE LA LISTE (25 cases) ---
    for(i = 0; i < 4; i++) { liste[i].type = DRAGON; liste[i].proprietaire = -1; }
    for(i = 4; i < 8; i++) { liste[i].type = ORC; liste[i].proprietaire = -1; }
    for(i = 8; i < 12; i++) { liste[i].type = NAZGUL; liste[i].proprietaire = -1; }
    for(i = 12; i < 16; i++) { liste[i].type = ARAIGNEE; liste[i].proprietaire = -1; }

    liste[16].type = TRESOR;   liste[16].proprietaire = -1;
    liste[17].type = TRESOR;   liste[17].proprietaire = -1;

    // Armes spéciales liées aux IDs des classes (0:GANDALF, 1:TAURIEL, etc.)
    liste[18].type = ARME_SPE; liste[18].proprietaire = 0; 
    liste[19].type = ARME_SPE; liste[19].proprietaire = 1; 
    liste[20].type = ARME_SPE; liste[20].proprietaire = 2; 
    liste[21].type = ARME_SPE; liste[21].proprietaire = 3; 

    liste[22].type = PORTAIL;  liste[22].proprietaire = -1;
    liste[23].type = TOTEM;    liste[23].proprietaire = -1;
    liste[24].type = TOTEM;    liste[24].proprietaire = -1;

    // Toutes les cases du labyrinthe sont cachées au début
    for(i = 0; i < 25; i++) {
        liste[i].est_decouverte = 0;
    }

    // --- 2. MÉLANGE DE FISHER-YATES ---
    for(i = 24; i > 0; i--) {
        int j = rand() % (i + 1);
        Case temp = liste[i];
        liste[i] = liste[j];
        liste[j] = temp;
    }

    // --- 3. REMPLISSAGE DU PLATEAU 6x6 ---
    for(int lig = 0; lig < TAILLE; lig++) {
        for(int col = 0; col < TAILLE; col++) {
            // Si on est dans le carré 5x5 (indices 0 à 4)
            if (lig < 5 && col < 5) {
                p.tableau[lig][col] = liste[compteur];
                compteur++;
            } 
            // Si on est sur la bordure (ligne 5 ou colonne 5), on crée des cases "BORD"
            else {
                p.tableau[lig][col].type = PORTAIL; // Ou un type VIDE/BORD si tu en as un
                p.tableau[lig][col].est_decouverte = 1; // Toujours visible
                p.tableau[lig][col].proprietaire = -1;
            }
        }
    }

    return p;
}
