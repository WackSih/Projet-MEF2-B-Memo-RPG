#include "memo_rpg.h"

void vide_buffer(){
    while(getchar()!='\n'){
    }
}

int main() {
    srand(time(NULL));
    int continuer = 1;
    int rejouer = 1;
    while (continuer != 0) {
        Personnage joueurs[4];
        int nb_joueurs;
        int menu;
        int verif;
        do{
            printf("\n=== BIENVENUE DANS MEMO-RPG ===\n"); //MENU D'ACCEUIL
            printf("1. Jouer une partie\n");
            printf("2. Voir le Hall of Fame\n");
            printf("0. Quitter\n");
            printf("Votre choix : ");
            verif=scanf("%d", &menu);
            vide_buffer();
            if(menu<0 || menu > 2){
                printf("Erreur, veuillez selectionner a nouveau.\n");
            }
        }while (menu<0 || menu > 2 || verif!=1 );//toujours un problème --> si on écrit nimp  pas de message d'erreur mais redemande quand même à l'utilisateur de re saisir
        if (menu == 0) break;
        if (menu == 2) {
            StatJoueur stats[100];
            int nb = charger_stats(stats, 100);
            printf("\n--- CLASSEMENT ---\n");
            printf("%-20s %8s %9s %8s %6s\n", "Joueur", "Parties", "Victoires", "Defaites", "Morts");
            printf("------------------------------------------------------------\n");
            for (int i = 0; i < nb; i++) {
                printf("%-20s %8d %9d %8d %6d\n",
                    stats[i].nom,
                    stats[i].parties,
                    stats[i].victoires,
                    stats[i].defaites,
                    stats[i].nmb_mort);
            }
            continue;
        }

        do{
            printf("Combien de joueurs (2-4) ? ");
            verif=scanf("%d", &nb_joueurs);
            vide_buffer();
        }while(nb_joueurs>4 || nb_joueurs<2 || verif!=1);

        select_perso(joueurs, nb_joueurs); 
        while(rejouer==1){ //DEBUT DE LA BOUCLE AVEC LES JOUEURS ET PERSOS CHOISIS
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

            do{
                printf("Voulez-vous rejouer avec les mêmes joueurs et personnages ?\n1. OUI\n0. NON\n"); //MENU POUR REJOUER
                printf("Choix : ");
                verif=scanf("%d", &rejouer);
                vide_buffer();
            }while(verif!=1 || rejouer<0 || rejouer>1);
        } // FIN DE LA PARTIE AVEC CES JOUEURS

       do{
            printf("\nQue voulez-vous faire ?\n");    //MENU DE FIN
            printf("1. Revenir au menu principal\n");
            printf("0. Quitter le programme\n");
            printf("Choix : ");
            verif=scanf("%d", &continuer);
            vide_buffer();
        }while(verif!=1 || continuer<0|| continuer>1);
    }
    return 0;
}

