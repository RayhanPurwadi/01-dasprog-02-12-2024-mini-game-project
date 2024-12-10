#include "game.h"

int calculate_x_text_center(const gamestate_t *game, int size) {
    return game->win.x/2 - size/2;
}

void make_text(int x, int y, const char* text) {
    mvaddstr(y, x, text);
}

void render_menu(gamestate_t *game) {
    int x, y;
    char text[][MAX_CONSOLE_WIDTH] = {
        "PONG",
        "by Rayhan Diah Purwadi (5024241032)",

        "[1] PLAY",
        "[2] Choose difficulty",
        "[3] Quit",

        "In any circumstances, press Ctrl+C to quit."
    };
    int ypos[] = { 4, 5, 7, 8, 9, 11 };
    const int componentCount = 6;

    for (int i = 0; i < componentCount; i++) {
        x = calculate_x_text_center(game, strlen(text[i]));
        y = ypos[i];
        make_text(x, y, text[i]);
    }
}

void render_game(gamestate_t *game) {

}

void render_settings(gamestate_t *game) {

}