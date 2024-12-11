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
    timeout(100);

    // game
    int x, y;
    char tmp[50] = {0};
    long long lastBallUpdate = timeInMilliseconds();
    vector2_t ball = { game->win.x/2, game->win.y/2 };
    vector2_t balldir = { 0, 0 };
    player_t players[2] = {
        { game->win.y/2 - PLAYER_HEIGHT/2 },
        { game->win.y/2 - PLAYER_HEIGHT/2 }
    };

    srand(time(0));
    balldir.x = rand() % 2 == 0 ? 1 : -1;
    balldir.y = rand() % 2 == 0 ? 1 : -1;

#define FULL_BLOCK "|"

    while (game->score[0] < 7 && game->score[1] < 7) {
        long long updateTime = timeInMilliseconds();
        clear();

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
        // sprintf(tmp, "Score: %lld", );
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

        if (rand() % 50 - (game->difficulty+1)*10 <= 20 && ball.x <= game->win.x/(3-game->difficulty))
            for (int i = 0; i < game->difficulty+1; i++)
                we_play(game, &ball, players); // TODO: Smooth out the drawing.

        for (int i = 0; i < PLAYER_HEIGHT; i++) {
            // Enemy
            make_text(1, players[0].y + i, FULL_BLOCK);
            // Player
            make_text(x, players[1].y + i, FULL_BLOCK);
        }

        // Update ball
        if (updateTime - lastBallUpdate >= 1000/BALL_SPEED) {
            we_ball(game, &ball, &balldir, players);
            ball.x += balldir.x;
            ball.y += balldir.y;
            lastBallUpdate = updateTime;
        }
        // Draw ball
        make_text(ball.x, ball.y, "O");

        refresh();

        int ch = getch();
        if (ch == KEY_UP) {
            players[1].y--;
        } else if (ch == KEY_DOWN) {
            players[1].y++;
        }
    }

#undef FULL_BLOCK
    // TODO: Render winning screen
    
    timeout(-1);
}

vector2_t vAdd(vector2_t const a, vector2_t const b) {
    return (vector2_t){ a.x + b.x, a.y + b.y };
}

void we_ball(gamestate_t *game, vector2_t *ball, vector2_t *dir, player_t const players[2]) {
    // Check window top and bottom collision
    vector2_t afterMovement = vAdd(*ball, *dir);
    if (afterMovement.y <= 0 || afterMovement.y >= game->win.y) {
        dir->y = -dir->y;
    } else if (afterMovement.x <= 0 || afterMovement.x >= game->win.x) {
        // GOAL!
        int isPlayer = afterMovement.x <= 0 ? 1 : 0;
        game->score[isPlayer]++;
        
        // Reset ball position
        ball->x = game->win.x/2;
        ball->y = game->win.y/2;
        dir->x = rand() % 2 == 0 ? 1 : -1;
        dir->y = rand() % 2 == 0 ? 1 : -1;
    } else if (
        (players[0].y <= ball->y && players[0].y + PLAYER_HEIGHT >= ball->y && ball->x <= 1+2) ||
        (players[1].y <= ball->y && players[1].y + PLAYER_HEIGHT >= ball->y && ball->x >= game->win.x-2-1)
    ) {
        dir->x = -dir->x;
        dir->y = -dir->y;
    }
}

void we_play(gamestate_t *game, vector2_t *ball, player_t players[2]) {
    int delta = (players[0].y - ball->y) + PLAYER_HEIGHT/2;
    
    players[0].y += delta > 0 ? -1 : 1;
}