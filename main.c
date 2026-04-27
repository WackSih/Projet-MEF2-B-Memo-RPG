#include "memo_rpg.h"



// --- Dans main.c ---
int main() {
    srand(time(NULL));
    int nb_joueurs = 2; // Ou scanf
    Personnage joueurs[4];

    // 1. On choisit les persos d'abord
    select_perso(joueurs, nb_joueurs); 

    // 2. On génère le plateau en lui passant le tableau des joueurs
    Plateau monPlateau = initialisation(joueurs, nb_joueurs);

    // 3. On place les joueurs
    depart(joueurs, nb_joueurs);

    deroulement_jeu(&monPlateau, joueurs, nb_joueurs);

    // Affichage du classement final
    StatJoueur stats[100];
    int nb_stats = charger_stats(stats, 100);
    printf("\n--- CLASSEMENT ---\n");
    for(int i = 0; i < nb_stats; i++){
        printf("%s : %d parties, %d victoires\n", stats[i].nom, stats[i].parties, stats[i].victoires);
    }
    return 0;
}
