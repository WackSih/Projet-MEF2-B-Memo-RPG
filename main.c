#include "memo_rpg.h"

int main() {
    srand(time(NULL)); // Indispensable pour le mélange du plateau !

    // 1. Initialisation
    Plateau monPlateau = initialisation();
    int nb_joueurs = 2; // On peut demander un scanf ici
    Personnage joueurs[4];

    // 2. Préparation des joueurs
    select_perso(joueurs, nb_joueurs);
    depart(joueurs, nb_joueurs);

    // 3. Boucle de jeu
    printf("\n--- DEBUT DU COMBAT ---\n");
    deroulement_jeu(&monPlateau, joueurs, nb_joueurs);

    return 0;
}
