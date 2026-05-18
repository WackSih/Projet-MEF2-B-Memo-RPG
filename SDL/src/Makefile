#première cible
all: exec_sdl

affichage_sdl.o : affichage_sdl.c memo_rpg.h
  gcc -c affichage_sdl.c -o affichage_sdl.o

init_plateau.o : init_plateau.c memo_rpg.h
	gcc -c init_plateau.c -o init_plateau.o

logique.o : logique.c memo_rpg.h
	gcc -c logique.c -o logique.o

sauvegarde.o : sauvegarde.c memo_rpg.h
	gcc -c sauvegarde.c -o sauvegarde.o

init_perso.o : init_perso.c memo_rpg.h
	gcc -c init_perso.c -o init_perso.o

exec_sdl : affichage_sdl.o init_perso.o init_plateau.o sauvegarde.o logique.o
	gcc affichage_sdl.o init_perso.o init_plateau.o sauvegarde.o logique.o -o exec_sdl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#effacer les fichiers de compilation
clean : 
  rm -f *.o
	rm exec_sdl
