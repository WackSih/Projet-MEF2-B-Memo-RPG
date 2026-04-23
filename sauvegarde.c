#include "memo_rpg.h"

int charger_stats(StatJoueur tableau[],int max_joueurs) {//on aura besoin d'un nombre maximum de joueur à enregistrer dans le fichier 
    FILE *fichier =NULL;
    fichier=fopen("stats.txt", "r");

    if (fichier == NULL){
        fichier=fopen("stats.txt","w");//crée un fichier vide si il n'y en a pas
        fclose(fichier);
        return 0;
    }

    int i = 0;
    //permet de remplir le tableau avec les donnée enregistrée du fichier
    while (i < max_joueurs && fscanf(fichier, "%s %d %d", tableau[i].nom, &tableau[i].parties, &tableau[i].victoires) == 3) {
        i++;
    }
    fclose(fichier);
    return i; // Retourne le nombre de joueurs chargés
}




//sauvegarde tous les joueurs gagnant dans le fichier 
//-> besoin d'une fonction dans le main ou autre part qui permet d'ajouter un nouveau joueur gagnant dans le tableau 
int sauvegarder_stats(StatJoueur tableau[],int nb_joueurs){

    FILE* fichier=NULL;
    fichier=fopen("stats.txt","w");
    if(fichier==NULL){
        printf("erreur lors de l'ouverture du fichier\n");
        return 0;//0 -> erreur de l'enregistrement
    }

    for (int i = 0; i < nb_joueurs; i++) {
        fprintf(fichier, "%s %d %d\n", tableau[i].nom, tableau[i].parties, tableau[i].victoires);
    }

    fclose(fichier);
    printf("Statistiques sauvegardées avec succès.\n");
    return 1; // enregistrement effectué
}
