#include"memo_rpg.h"

Plateau initialisation(){
    Plateau p;
    Case liste[TAILLE*TAILLE]; //liste des 25 cases à remplir
    int i; // Pour toutes les boucles
    int compteur = 0; // Pour remplir le tableau à la fin

    for(i=0 ; i<4 ; i++){
        liste[i].type = DRAGON;
        liste[i].proprietaire = -1;
    }
    for(i=4 ; i<8 ; i++){
        liste[i].type = ORC;
        liste[i].proprietaire = -1;
    }
    for(i=8 ; i<12 ; i++){
        liste[i].type = NAZGUL;
        liste[i].proprietaire = -1;
    }
    for(i=12 ; i<16 ; i++){
        liste[i].type = ARAIGNEE;
        liste[i].proprietaire = -1;
    }

    liste[16].type = TRESOR; liste[16].proprietaire = -1;
    liste[17].type = TRESOR; liste[17].proprietaire = -1;

    liste[18].type = TRESOR_PERSO; liste[18].proprietaire = 0; // Joueur 1
    liste[19].type = TRESOR_PERSO; liste[19].proprietaire = 1; // Joueur 2
    liste[20].type = TRESOR_PERSO; liste[20].proprietaire = 2; // Joueur 3
    liste[21].type = TRESOR_PERSO; liste[21].proprietaire = 3; // Joueur 4

    liste[22].type = PORTAIL; liste[22].proprietaire = -1;
    liste[23].type = TOTEM; liste[23].proprietaire = -1;
    liste[24].type = TOTEM; liste[24].proprietaire = -1;

    for(i=0 ; i<(TAILLE*TAILLE) ; i++){
        liste[i].est_decouverte = 0;
    }

    for(i=((TAILLE*TAILLE)-1) ; i>0 ; i--){      //Mélange parfait de Fisher-Yates
        int j = rand()%(i+1);
        Case temp = liste[i];
        liste[i] = liste[j];
        liste[j] = temp;
    }

    for(int lig=0 ; lig<TAILLE ; lig++){
        for(int col=0 ; col<TAILLE ; col++){
            p.tableau[lig][col] = liste[compteur];
            compteur++;
        }
    }

    return p;
}
