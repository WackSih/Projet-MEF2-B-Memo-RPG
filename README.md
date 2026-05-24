# Projet-MEF2-B-Memo-RPG

Ce jeu est un memory RPG inspiré de l'univers du Seigneur des Anneaux. 
Il est codé exclusivement en langage C.

Le projet est divisé en deux dossiers distincts : une version classique jouable dans le **Terminal**, et une version graphique utilisant la **SDL**.

---

## Version Terminale

Cette version classique propose une expérience directement jouable depuis l'invite de commandes. Tous les fichiers sources (`.c`, `.h`) et le Makefile se trouvent directement à la racine du dossier.

### ⚠️ Prérequis importants
1. **Fichiers sources :** Assurez-vous que tous les fichiers `.c` et `.h` sont présents dans le dossier.
2. **Configuration :** Le fichier `Makefile` doit se situer au même endroit que les fichiers sources.

### Compilation et Exécution via le Makefile

Ouvrez un terminal dans le dossier et utilisez le fichier `Makefile` fourni :

**Pour compiler :**
> make

**Pour lancer le jeu :**
* **Linux :** `./exec`
* **Windows :** `.\exec.exe`

**Pour nettoyer les fichiers objets (`.o`) et l'exécutable :**
> make clean

### Compilation manuelle (Alternative sans Makefile)

Si vous préférez compiler directement à la main dans votre terminal :

#### En ligne de commande sous Linux :
> gcc main.c init_plateau.c init_perso.c sauvegarde.c logique.c -o exec

**Pour lancer :** `./exec`

#### En ligne de commande sous Windows (PowerShell / CMD) :
> gcc main.c init_plateau.c init_perso.c sauvegarde.c logique.c -o exec.exe

**Pour lancer :** `.\exec.exe`

---

## Version SDL

Cette version propose une interface graphique complète et une gestion sonore pour une expérience de jeu immersive. Elle possède sa propre arborescence avec un dossier `src/` pour le code et un dossier `assets/` pour les ressources.

### ⚠️ Prérequis importants
1. **Dossier `assets/` :** Assurez-vous que le dossier `assets/` (contenant les images `.png`, la police `police.ttf` et les musiques `.mp3`) est bien présent à la racine du dossier SDL.
2. **Fichiers `.dll` (Windows uniquement) :** Pour pouvoir lancer l'exécutable sous Windows, les fichiers de liaison dynamique de la SDL (`SDL2.dll`, `SDL2_image.dll`, `SDL2_ttf.dll` et `SDL2_mixer.dll`) doivent impérativement être copiés à la racine de ce même dossier.

### Compilation et Exécution via le Makefile

Si vous utilisez le fichier `Makefile_sdl` dédié à la version graphique :

**Pour compiler :**
> make 

**Pour lancer le jeu :**
* **Linux :** `./exec_sdl`
* **Windows :** `.\exec_sdl.exe`

**Pour nettoyer les fichiers objets (`.o`) et l'exécutable :**
> make clean

### Compilation manuelle (Alternative sans Makefile)

Si vous préférez compiler directement à la main dans votre terminal depuis la racine du dossier SDL :

#### En ligne de commande sous Linux :
> gcc src/affichage_sdl.c src/init_plateau.c src/init_perso.c src/sauvegarde.c src/logique.c -o exec_sdl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

**Pour lancer :** `./exec_sdl`

#### En ligne de commande sous Windows (PowerShell / CMD) :
> gcc src/affichage_sdl.c src/init_plateau.c src/init_perso.c src/sauvegarde.c src/logique.c -o exec_sdl.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

**Pour lancer :** `.\exec_sdl.exe`
