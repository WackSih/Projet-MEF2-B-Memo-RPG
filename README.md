# Projet-MEF2-B-Memo-RPG

Ce jeu est codé exclusivement en langage c

##Version Terminale :

### Commande de Compilation dans le Terminal (Linux) :
Après s'être placé dans le bon dossier avec les différents fichiers du jeu (via la commandes 'cd'), on utilise le compilateur gcc :

> gcc -o jeu main.c memo_rpg.h init_perso.c init_plateau.c logique.c sauvegarde.c

suivi de :

> ./jeu

afin de lancer le jeu.

##Version SDL (graphique) :

### Commande de Compilation dans le Terminal (Linux) :
On se place toujours dans le bon dossier avec la bonne version (SDL), dans le terminal on écrit :

> gcc -o jeu main.c

