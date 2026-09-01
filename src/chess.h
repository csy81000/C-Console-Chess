#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#define BOARD_SIZE 8
#define EMPTY_SQUARE '*'

typedef char Board[BOARD_SIZE][BOARD_SIZE];

typedef enum Player {
    PLAYER_WHITE,
    PLAYER_BLACK
} Player;

void initialize_console(void);
void clear_console(void);
void wait_for_enter(void);
void draw_board(
    const char board[BOARD_SIZE][BOARD_SIZE],
    Player player,
    int selected_row,
    int selected_column
);
void show_help(void);

void reset_board(Board board);
bool parse_position(const char *input, int *row, int *column);
bool player_owns_piece(char piece, Player player);
bool is_legal_move(
    const char board[BOARD_SIZE][BOARD_SIZE],
    Player player,
    int from_row,
    int from_column,
    int to_row,
    int to_column
);
bool move_piece(
    Board board,
    Player player,
    int from_row,
    int from_column,
    int to_row,
    int to_column
);
bool has_king(const char board[BOARD_SIZE][BOARD_SIZE], Player player);

int run_game(void);

#endif
