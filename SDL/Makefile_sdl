# Cible principale
all: exec_sdl

# Compilation des fichiers objets
affichage_sdl.o : src/affichage_sdl.c src/memo_rpg.h
	gcc -c src/affichage_sdl.c -o affichage_sdl.o

init_plateau.o : src/init_plateau.c src/memo_rpg.h
	gcc -c src/init_plateau.c -o init_plateau.o

logique.o : src/logique.c src/memo_rpg.h
	gcc -c src/logique.c -o logique.o

sauvegarde.o : src/sauvegarde.c src/memo_rpg.h
	gcc -c src/sauvegarde.c -o sauvegarde.o

init_perso.o : src/init_perso.c src/memo_rpg.h
	gcc -c src/init_perso.c -o init_perso.o

# Édition de liens (Création de l'exécutable graphique)
exec_sdl : affichage_sdl.o init_perso.o init_plateau.o sauvegarde.o logique.o
	gcc affichage_sdl.o init_perso.o init_plateau.o sauvegarde.o logique.o -o exec_sdl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Effacer les fichiers de compilation
clean : 
	rm -f *.o
	rm -f exec_sdl
