build:
	gcc -Wall -pedantic -I includes src/utils.c src/game.c src/main.c -o game -lncursesw