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
    return 0;
}
