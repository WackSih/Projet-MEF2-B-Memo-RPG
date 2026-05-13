#première cible
all: exec

main.o : main.c memo_rpg.h
	gcc -c main.c -o main.o

init_plateau.o : init_plateau.c memo_rpg.h
	gcc -c init_plateau.c -o init_plateau.o

logique.o : logique.c memo_rpg.h
	gcc -c logique.c -o logique.o

sauvegarde.o : sauvegarde.c memo_rpg.h
	gcc -c sauvegarde.c -o sauvegarde.o

init_perso.o : init_perso.c memo_rpg.h
	gcc -c init_perso.c -o init_perso.o

exec : main.o init_perso.o init_plateau.o sauvegarde.o logique.o
	gcc main.o init_perso.o init_plateau.o sauvegarde.o logique.o -o exec

#effacer les fichiers de compilation
clean : 
	rm -f *.o
	rm exec