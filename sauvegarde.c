#include "memo_rpg.h"

int charger_stats(StatJoueur tableau[],int max_joueurs) {
    FILE *fichier =NULL;
    fichier=fopen("stats.txt", "r");

    if (fichier == NULL){
        fichier=fopen("stats.txt","w");//crée un fichier vide si il n'y en a pas
        fclose(fichier);
        return 0;
    }

    int i = 0;
    
    while (i < max_joueurs && fscanf(fichier, "%s %d %d", tableau[i].nom, &tableau[i].parties, &tableau[i].victoires) == 3) {
        i++;
    }
    fclose(fichier);
    return i; // Retourne le nombre de joueurs chargés
}




//sauvegarde tous les joueurs gagnant dans le fichier 
int sauvegarder_stats(StatJoueur tableau[],int nb_joueurs){

    FILE* fichier=NULL;
    fichier=fopen("stats.txt","w");
    if(fichier==NULL){
        printf("erreur lors de l'ouverture du fichier\n");
        return 0;// 0 -> erreur de l'enregistrement
    }

    for (int i = 0; i < nb_joueurs; i++) {
        fprintf(fichier, "%s %d %d\n", tableau[i].nom, tableau[i].parties, tableau[i].victoires);
    }

    fclose(fichier);
    
    return 1; // enregistrement effectué
}


void mettre_a_jour_stats(const char* nom, int a_gagne) {
    StatJoueur tableau[100];
    int nb = charger_stats(tableau, 100);

    // Cherche si le joueur existe déjà
    int trouve = -1;
    for (int i = 0; i < nb; i++) {
        if (strcmp(tableau[i].nom, nom) == 0) {
            trouve = i;
            break;
        }
    }

    if (trouve == -1) {
        // Nouveau joueur : on l'ajoute
        strncpy(tableau[nb].nom, nom,49);
        tableau[nb].parties = 1;
        tableau[nb].victoires = a_gagne;
        nb++;
    } else {
        // Joueur existant : on met à jour
        tableau[trouve].parties++;
        tableau[trouve].victoires += a_gagne;
    }

    sauvegarder_stats(tableau, nb);
}
