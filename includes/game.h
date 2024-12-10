#ifndef __GAME_H
#define __GAME_H

#include <string.h>
#include <ncursesw/curses.h>

// 4 chars
#define PLAYER_HEIGHT 4
#define MAX_CONSOLE_WIDTH 50

typedef enum { VIEW_MENU, VIEW_GAME, VIEW_SETTINGS } VIEW;
typedef enum { DIFFICULTY_EASY, DIFFICULTY_NORMAL, DIFFICULTY_HARD } DIFFICULTY;

typedef struct player_t {
    int y;
} player_t;

typedef struct gamestate_t {
    VIEW view;
    DIFFICULTY difficulty;
    int isQuitting;
    unsigned short score[2];
    struct win {
        unsigned int x;
        unsigned int y;
    } win;
} gamestate_t;

int calculate_x_text_center(gamestate_t const *game, int size);
void make_text(int x, int y, const char* text);
void render_menu(gamestate_t *game);
void render_game(gamestate_t *game);
void render_settings(gamestate_t *game);

#endif
