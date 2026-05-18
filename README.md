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

> gcc affichage_sdl.c logique.c init_plateau.c sauvegarde.c init_perso.c -o memo_rpg -lSDL2 -lSDL2_image -lSDL2_ttf

Commande windows gcc affichage_sdl.c init_plateau.c init_perso.c sauvegarde.c logique.c -o memo_rpg_menus.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


commande linux gcc affichage_sdl.c init_plateau.c init_perso.c sauvegarde.c logique.c -o memo_rpg -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
