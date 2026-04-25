#ifndef MEMO_RPG_H
#define MEMO_RPG_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define TAILLE 5

// Enums
typedef enum { GANDALF, TAURIEL, GOLLUM, GIMLI } Classe;
typedef enum { BATON, ARC_M, ANNEAU, HACHE } Arme_spe;
typedef enum { DRAGON, ORC, NAZGUL, ARAIGNE, PORTAIL, TOTEM, TRESOR, ARME_SPE, ARAIGNEE, ARC_M, BATON, ANNEAU, HACHE } Type_case;
typedef enum { ARC, EPEE, BDF, LANCE } Arme;

// Structures
typedef struct {
    char nomJoueur[50];
    Classe perso;
    Arme_spe arme_a_trouver;   
    int aLarme;         
    int aLeTresor;
    Arme arme_actuelle;
    int ligne;
    int colonne;
} Personnage;

typedef struct {
    Type_case type;
    Arme arme_choisie;
    int est_decouverte; 
    int proprietaire; 
} Case;

typedef struct {
    Case tableau[TAILLE][TAILLE];
} Plateau;

typedef struct {
    char nom[50];
    int parties;
    int victoires;
} StatJoueur;

// Prototypes (Indispensables pour lier les fichiers)
Plateau initialisation();
void depart(Personnage tab_joueurs[], int nb_joueurs);
void select_perso(Personnage tab_joueurs[], int nb_joueurs);
Personnage* choix_arme(Personnage *x);
int verifcaselibre(Plateau* tab, int colonne_new, int ligne_new);
void deplacement(Personnage* x, Plateau* tab);
void resolution_case(Personnage* x, Plateau* tab);
void afficher_plateau(Plateau* p, Personnage* joueurs, int nb_joueurs);
void deroulement_jeu(Plateau* tab, Personnage* joueur, int nb_joueurs);
void reset_tableau(Personnage* x, Plateau* tab);
int charger_stats(StatJoueur tableau[], int max_joueurs);
int sauvegarder_stats(StatJoueur tableau[], int nb_joueurs);

#endif
