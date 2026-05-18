# Projet-MEF2-B-Memo-RPG

Ce jeu est un memory RPG inspiré de l'univers du Seigneur des Anneaux. 
Il est codé exclusivement en langage C.

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

Cette version propose une interface graphique complète et une gestion sonore pour une expérience de jeu immersive.

### ⚠️ Prérequis importants
1. **Dossier `assets/` :** Assurez-vous que le dossier `assets/` (contenant les images `.png`, la police `police.ttf` et les musiques `.mp3`) est bien présent à la racine du projet, juste à côté de vos fichiers de configuration.
2. **Fichiers `.dll` (Windows uniquement) :** Pour pouvoir lancer l'exécutable sous Windows, les fichiers de liaison dynamique de la SDL (`SDL2.dll`, `SDL2_image.dll`, `SDL2_ttf.dll`, `SDL2_mixer.dll`) doivent impérativement être copiés à la racine du projet.

### Compilation et Exécution via le Makefile

Si vous utilisez le fichier `Makefile_sdl` dédié à la version graphique :

**Pour compiler :**
> make -f Makefile_sdl

**Pour lancer le jeu :**
* **Linux :** `./exec_sdl`
* **Windows :** `.\exec_sdl.exe`

**Pour nettoyer les fichiers objets (`.o`) et l'exécutable :**
> make -f Makefile_sdl clean

---

### Compilation manuelle (Alternative sans Makefile)

Si vous préférez compiler directement à la main dans votre terminal depuis la racine du projet :

#### En ligne de commande sous Linux :
> gcc src/affichage_sdl.c src/init_plateau.c src/init_perso.c src/sauvegarde.c src/logique.c -o exec_sdl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

**Pour lancer :** `./exec_sdl`

#### En ligne de commande sous Windows (PowerShell / CMD) :
> gcc src/affichage_sdl.c src/init_plateau.c src/init_perso.c src/sauvegarde.c src/logique.c -o exec_sdl.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

**Pour lancer :** `.\exec_sdl.exe`
