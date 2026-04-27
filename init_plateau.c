#include "memo_rpg.h"

Plateau initialisation() {
    Plateau p;
    Case liste[25]; 
    int i, compteur = 0;
    for(i = 0; i < 4; i++) { liste[i].type = DRAGON; liste[i].proprietaire = -1; }
    for(i = 4; i < 8; i++) { liste[i].type = ORC; liste[i].proprietaire = -1; }
    for(i = 8; i < 12; i++) { liste[i].type = NAZGUL; liste[i].proprietaire = -1; }
    for(i = 12; i < 16; i++) { liste[i].type = ARAIGNEE; liste[i].proprietaire = -1; }
    liste[16].type = TRESOR; liste[16].proprietaire = -1;
    liste[17].type = TRESOR; liste[17].proprietaire = -1;
    liste[18].type = ARME_SPE; liste[18].proprietaire = 0; 
    liste[19].type = ARME_SPE; liste[19].proprietaire = 1; 
    liste[20].type = ARME_SPE; liste[20].proprietaire = 2; 
    liste[21].type = ARME_SPE; liste[21].proprietaire = 3; 
    liste[22].type = PORTAIL; liste[22].proprietaire = -1;
    liste[23].type = TOTEM; liste[23].proprietaire = -1;
    liste[24].type = TOTEM; liste[24].proprietaire = -1;
    for(i = 0; i < 25; i++) {
        liste[i].est_decouverte = 0;
    }
    // --- 2. MÉLANGE ---
    for(i = 24; i > 0; i--) {
        int j = rand() % (i + 1);
        Case temp = liste[i];
        liste[i] = liste[j];
        liste[j] = temp;
    }
    // --- 3. REMPLISSAGE DU PLATEAU 7x7 ---
    for(int lig = 0; lig < TAILLE; lig++) {
        for(int col = 0; col < TAILLE; col++) {
            // ZONE DE JEU (Le carré 5x5 central : indices 1 à 5)
            if (lig >= 1 && lig <= 5 && col >= 1 && col <= 5) {
                p.tableau[lig][col] = liste[compteur];
                compteur++;
            } 
            // LES 4 CASES DE DÉPART (Pointes de la croix)
            else if ((lig == 0 && col == 3) || (lig == 3 && col == 0) || 
                     (lig == 6 && col == 3) || (lig == 3 && col == 6)) {
                p.tableau[lig][col].type = PORTAIL; // Case de spawn
                p.tableau[lig][col].est_decouverte = 1; 
                p.tableau[lig][col].proprietaire = -1;
            }
            // TOUT LE RESTE (Les coins "morts")
            else {
                p.tableau[lig][col].type = VIDE;
                p.tableau[lig][col].est_decouverte = 1; // On les affiche comme vides
                p.tableau[lig][col].proprietaire = -1;
            }
        }
    }
    return p;
}
