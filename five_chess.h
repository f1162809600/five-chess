#ifndef _FILE_CHESS_H_
#define _FILE_CHESS_H_

#define CHESS_BOARD_ROW 10
#define CHESS_BOARD_COL 10

#define CHESS_NUM       5

typedef struct direction {
    int dx;
    int dy;
    char name[16];
} dir_t;

#endif  //_FILE_CHESS_H_
