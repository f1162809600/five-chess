#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "five_chess.h"

struct direction dirs[8] = {
    {-1, 0, "up"},
    {1, 0, "down"},
    {0, -1, "left"},
    {0, 1, "right"},
    {-1, -1, "left-up"},
    {1, 1, "right-down"},
    {1, -1, "left-down"},
    {-1, 1, "right-up"},
};

static int chess_board[CHESS_BOARD_ROW][CHESS_BOARD_COL];

void chess_board_init(void)
{
    int i, j;

    for (i = 0; i < CHESS_BOARD_ROW; i ++) {
        for (j = 0; j < CHESS_BOARD_COL; j ++) {
            chess_board[i][j] = 0;
        }
    }
}

bool is_draw(void)
{
    int i, j;

    for (i = 0; i < CHESS_BOARD_ROW; i ++) {
        for (j = 0; j < CHESS_BOARD_COL; j ++) {
            if(chess_board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void clear_screen(void)
{
    system("clear");
}

void chess_board_display(void)
{
    int i, j;

    printf("  ");

    for (i = 0; i < CHESS_BOARD_COL; i ++) {
        printf(" %d", i);
    }
    putchar('\n');

    for (i = 0; i < CHESS_BOARD_COL + 1; i ++) {
        printf(" %c", '-');
    }
    putchar('\n');

    for (i = 0; i < CHESS_BOARD_ROW; i ++) {
        printf("%d|", i);
        for (j = 0; j < CHESS_BOARD_COL; j ++) {
            printf(" %d", chess_board[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void get_user_input(int *px, int *py, int who)
{
    printf("Player%d Input: ", who);

    while(scanf("%d%d", px, py) != 2) {
        printf("Bad Input, Re-try.\n");
        while(getchar() != '\n');
    }
    getchar();
}

bool is_on_board(int x, int y)
{
    if ((x >= 0 && x < CHESS_BOARD_ROW) &&
            (y >= 0 && y < CHESS_BOARD_COL)) {
        return true;
    }
    return false;
}

bool is_empty(int x, int y)
{
    return chess_board[x][y] == 0;
}

void move_in_chess(int x, int y, int who)
{
    chess_board[x][y] = who;
}

int chess_counter(int x, int y, dir_t *dir)
{
    int nx, ny;
    int counter = 0;

    nx = x;
    ny = y;

    while(true) {
        nx += dir->dx;
        ny += dir->dy;

        if (! is_on_board(nx, ny)) {
            break;
        }

        if (chess_board[nx][ny] != chess_board[x][y]) {
            break;
        }
        counter ++;
    }
    return counter;
}

bool is_win(int x, int y)
{
    int i;

    for (i = 0; i < 4; i ++) {
        int counter1 = chess_counter(x, y, &(dirs[i * 2]));
        int counter2 = chess_counter(x, y, &(dirs[i * 2 + 1]));

        if (counter1 + counter2 + 1 >= CHESS_NUM) {
            return true;
        }
    }
    return false;
}

void five_chess(void)
{
    int who;
    int x, y;
    int step = 0;

    chess_board_init();

    while(true) {

        clear_screen();
        chess_board_display();

        who = step % 2 + 1;

        get_user_input(&x, &y, who);


        if (! is_on_board(x, y)) {
            printf("Bad Location, Re-try.\n");
            getchar();
            continue;
        }

        if (! is_empty(x, y)) {
            printf("Not Empty, Re-try.\n");
            getchar();
            continue;
        }

        move_in_chess(x, y, who);

        if (is_win(x, y)) {
            clear_screen();
            chess_board_display();
            printf("Player%d win.\n", who);
            break;
        }

        if (is_draw()) {
            printf("Draw, Game Over.\n");
            break;
        }

        step ++;
    }
}

int main(int argc, char *argv[])
{
    five_chess();
    return 0;
}

