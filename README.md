# Projet-MEF2-B-Memo-RPG

Ce jeu est un memory RPG inspiré de l'univers du Seigneur des Anneaux. 
Il est codé exclusivement en langage C.

Le projet dispose d'une architecture propre séparant le code source (dossier `src/`) et les ressources multimédias (dossier `assets/`).

---

## Version Terminale

### Compilation (Linux & Windows via MSYS2)
Ouvrez un terminal dans le dossier principal du jeu et utilisez la commande `make` pour compiler le projet grâce au Makefile fourni :

> make

### Exécution
Pour lancer le jeu, tapez la commande suivante :

> ./exec

*(Sur Windows, tapez : `.\exec.exe`)*

### Nettoyage
Une fois la partie terminée, vous pouvez nettoyer les fichiers de compilation (`.o` et exécutables) avec la commande :

> make clean

---

## Version SDL

**⚠️ Prérequis important :** Assurez-vous que le dossier `assets/` contenant toutes les images, polices et musiques est bien présent à la racine du projet, à côté de l'exécutable. Sur Windows, les fichiers `.dll` de la SDL2 doivent également se trouver dans ce dossier.

### Compilation et Exécution (Linux)
Compilez le jeu en liant les bibliothèques SDL2 avec la commande suivante :

> gcc src/affichage_sdl.c src/init_plateau.c src/init_perso.c src/sauvegarde.c src/logique.c -o memo_rpg_sdl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Pour lancer le jeu :
> ./memo_rpg_sdl

### Compilation et Exécution (Windows)
Dans le terminal PowerShell ou CMD, tapez la commande suivante pour compiler :

> gcc src/affichage_sdl.c src/init_plateau.c src/init_perso.c src/sauvegarde.c src/logique.c -o memo_rpg_sdl.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Pour lancer le jeu :
> .\memo_rpg_sdl.exe

---
*Amusez-vous bien et que le meilleur aventurier gagne !*
