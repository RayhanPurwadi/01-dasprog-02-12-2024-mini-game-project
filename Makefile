build:
	gcc -Wall -pedantic -DNCURSES_WIDECHAR=1 -I includes src/utils.c src/game.c src/main.c -o game -lncursesw