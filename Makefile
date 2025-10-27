app: main.o game.o
	gcc main.o game.o -o app

main.o: main.c
	gcc -c main.c

game.o: game.c game.h
	gcc -c game.c

clean:
	rm *.o
