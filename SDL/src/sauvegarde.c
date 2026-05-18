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
    
    while (i < max_joueurs && fscanf(fichier, "%s %d %d %d %d", tableau[i].nom,&tableau[i].parties,&tableau[i].victoires,&tableau[i].defaites,&tableau[i].nmb_mort) == 5) {
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
        fprintf(fichier, "%s %d %d %d %d\n",tableau[i].nom,tableau[i].parties,tableau[i].victoires,tableau[i].defaites,tableau[i].nmb_mort);
    }

    fclose(fichier);
    
    return 1; // enregistrement effectué
}

// a_gagne  : 1 si ce joueur a gagné la partie, sinon 0
// a_perdu  : 1 si la partie est finie et qu'un autre a gagné, sinon 0
// morts    : nombre de fois que ce joueur est mort contre un monstre CE tour
void mettre_a_jour_stats(const char* nom, int a_gagne, int a_perdu, int morts) {
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
        // Nouveau joueur
        strncpy(tableau[nb].nom, nom, 49);
        tableau[nb].nom[49] = '\0';//ajout manuelle de \0 car strcpy ne le fait pas automatiquement
        tableau[nb].parties  = 1;
        tableau[nb].victoires = a_gagne;
        tableau[nb].defaites  = a_perdu;
        tableau[nb].nmb_mort  = morts;
        nb++;
    } else {
        tableau[trouve].parties++;
        tableau[trouve].victoires += a_gagne;
        tableau[trouve].defaites  += a_perdu;
        tableau[trouve].nmb_mort  += morts;
    }

    sauvegarder_stats(tableau, nb);
}
