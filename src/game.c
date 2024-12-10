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

    // Register events
    while (1) {
        char ch = getch();
        if (ch == '1') { game->view = VIEW_GAME; break; }
        else if (ch == '2') { game->view = VIEW_SETTINGS; break; }
        else if (ch == '3') { game->isQuitting = true; break; }
    }
}

void render_settings(gamestate_t *game) {
    int x, y;
    char text[][MAX_CONSOLE_WIDTH] = {
        "SETTINGS",

        "Choose your difficulty:",
        "[1] Easy",
        "[2] Normal",
        "[3] Hard",

        "[0] Cancel"
    };
    int ypos[] = { 4, 6, 7, 8, 9, 11 };
    const int componentCount = 6;

    for (int i = 0; i < componentCount; i++) {
        x = calculate_x_text_center(game, strlen(text[i]));
        y = ypos[i];
        make_text(x, y, text[i]);
    }

    // Register events
    game->view = VIEW_MENU;
    while (1) {
        char ch = getch();
        if (ch == '1') { game->difficulty = DIFFICULTY_EASY; break; }
        else if (ch == '2') { game->difficulty = DIFFICULTY_NORMAL; break; }
        else if (ch == '3') { game->difficulty = DIFFICULTY_HARD; break; }
        else if (ch == '0') { break; }
    }
}


void render_game(gamestate_t *game) {
    // init
    halfdelay(1);

    // game
    int x, y;
    char tmp[50] = {0};
    struct { int x; int y; } ball = { game->win.x/2, game->win.y/2 };
#define FULL_BLOCK "|"

    while (game->score[0] < 7 && game->score[1] < 7) {
        if (game->clear) { clear(); game->clear = 0; }
        
        // Render static text
        x = calculate_x_text_center(game, strlen("GAME ON"));
        y = 1;
        make_text(x, y, "GAME ON");

        
        strcpy(tmp, "ENEMY");
        x = calculate_x_text_center(game, strlen(tmp))/2;
        y = game->win.y-1;
        make_text(x, y, tmp);

        strcpy(tmp, "PLAYER");
        x = calculate_x_text_center(game, strlen(tmp));
        x += x/2;
        y = game->win.y-1;
        make_text(x, y, tmp);

        // Render scores
        sprintf(tmp, "Score: %d", game->score[0]);
        x = calculate_x_text_center(game, strlen(tmp))/2;
        y = 1;
        make_text(x, y, tmp);

        sprintf(tmp, "Score: %d", game->score[1]);
        x = calculate_x_text_center(game, strlen(tmp));
        x += x/2;
        y = 1;
        make_text(x, y, tmp);

        // Render players
        x = game->win.x-2;
        y = game->win.y/2 - PLAYER_HEIGHT/2;

        for (int i = 0; i < PLAYER_HEIGHT; i++) {
            // Enemy
            make_text(1, y + i, FULL_BLOCK);
            // Player
            make_text(x, y + i, FULL_BLOCK);
        }

        refresh();
    }

#undef FULL_BLOCK
    // TODO: Render winning screen
    
    nocbreak();
}