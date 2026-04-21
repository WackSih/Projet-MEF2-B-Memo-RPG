#include "memo_rpg.h"

//création des différentes structures


typedef enum { GANDALF, TAURIEL, GOLLUM, GIMLI } Classe;
typedef enum { BATON, ARC_M, ANNEAU, HACHE } Arme_spe;

typedef struct {
    char nomJoueur[50]; // taille des tableaux certainement à ajuster plus tard en fonction de ce que saisie le joueur
    Classe perso;
    Arme_spe arme_a_trouver;   
    int aLarme;         
    int aLeTresor;
    Arme arme_actuelle;
    int ligne;
    int colone;
} Personnage;

typedef enum{DRAGON, ORC , NAZGUL , ARAIGNE , PORTAIL , TOTEM , TRESOR , ARME_SPE}Type_case;
typedef enum {ARC , EPE , BDF , LANCE}Arme;

typedef struct {
    Type_case type;
    Arme arme_choisie;
    int est_decouverte;
    int proprietaire; // -1 si ce n'est pas un trésor perso, {0,1,2,3} selon le joueur dont c'est le trésor
}Case;

typedef struct {
    Case tableau[TAILLE][TAILLE]
}Plateau; // Pour faciliter l'implémentation du plateau et épurer le main()
