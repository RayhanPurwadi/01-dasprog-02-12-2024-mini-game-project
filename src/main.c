#include <stdlib.h>
#include <ncursesw/curses.h>
#include <signal.h>

#include "utils.h"
#include "game.h"

int main() {
    initscr();
    register_grace_shutdowns();
    
    noecho();
    cbreak();

    clear();
    refresh();

    gamestate_t game = { VIEW_MENU, DIFFICULTY_EASY, 0, { 0, 0 } };
    getmaxyx(stdscr, game.win.y, game.win.x);

    while (!game.isQuitting) {
        clear();
        switch (game.view) {
            case VIEW_MENU:
                render_menu(&game);
                break;
            case VIEW_GAME:
                render_game(&game);
                break;
            case VIEW_SETTINGS:
                render_settings(&game);
                break;
        }
        refresh();
    }

    grace_shutdown(0);

    return 0;
}