2048 : func.o main.o
	gcc -o $@ func.o main.o -lncurses

func.o : func.c include/2048lib.h
	gcc -c func.c

main.o : main.c include/2048lib.h
	gcc -c main.c
