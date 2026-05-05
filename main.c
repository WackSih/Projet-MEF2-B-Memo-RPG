#include "memo_rpg.h"

int main() {
    srand(time(NULL));
    int continuer = 1;

    while (continuer != 0) {
        Personnage joueurs[4];
        int nb_joueurs;
        do{
        printf("\n=== BIENVENUE DANS MEMO-RPG ===\n");
        printf("1. Jouer une partie\n");
        printf("2. Voir le Hall of Fame\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        int menu;
        scanf("%d", &menu);
        if(menu<0 || menu > 2){
            printf("Erreur, veuillez selectionner a nouveau.\n");
        }
        }while (menu<0 || menu > 2);
        if (menu == 0) break;
        if (menu == 2) {
            StatJoueur stats[100];
            int nb = charger_stats(stats, 100);
            printf("\n--- CLASSEMENT ---\n");
            for(int i = 0; i < nb; i++) printf("%s : %d victoires\n", stats[i].nom, stats[i].victoires);
            continue;
        }

        printf("Combien de joueurs (2-4) ? ");
        scanf("%d", &nb_joueurs);

        select_perso(joueurs, nb_joueurs); 
        Plateau monPlateau = initialisation(joueurs, nb_joueurs); 
        depart(joueurs, nb_joueurs); 

        time_t debut = time(NULL);
        deroulement_jeu(&monPlateau, joueurs, nb_joueurs); 
        time_t fin = time(NULL);

        printf("\n--- LA PARTIE EST FINIE (Duree : %ld secondes) ---\n", fin - debut);
        for(int i = 0; i < TAILLE; i++) {
            for(int j = 0; j < TAILLE; j++) {
                monPlateau.tableau[i][j].est_decouverte = 1;
            }
        }
        afficher_plateau(&monPlateau, joueurs, nb_joueurs); 

        printf("\nQue voulez-vous faire ?\n");
        printf("1. Revenir au menu principal\n");
        printf("0. Quitter le programme\n");
        printf("Choix : ");
        scanf("%d", &continuer);
    }
    return 0;
}
