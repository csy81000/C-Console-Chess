#include "chess.h"

#include <ctype.h>
#include <stdlib.h>


static bool is_inside_board(int row, int column)
{
    return row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE;
}


static bool is_empty(char piece)
{
    return piece == EMPTY_SQUARE;
}


bool player_owns_piece(char piece, Player player)
{
    unsigned char value = (unsigned char)piece;

    if (is_empty(piece)) {
        return false;
    }
    return player == PLAYER_WHITE ? isupper(value) != 0 : islower(value) != 0;
}


static bool same_side(char first, char second)
{
    unsigned char first_value = (unsigned char)first;
    unsigned char second_value = (unsigned char)second;

    if (is_empty(first) || is_empty(second)) {
        return false;
    }
    return (isupper(first_value) && isupper(second_value))
        || (islower(first_value) && islower(second_value));
}


static int direction(int value)
{
    return (value > 0) - (value < 0);
}


static bool path_is_clear(
    const char board[BOARD_SIZE][BOARD_SIZE],
    int from_row,
    int from_column,
    int to_row,
    int to_column
)
{
    int row_step = direction(to_row - from_row);
    int column_step = direction(to_column - from_column);
    int row = from_row + row_step;
    int column = from_column + column_step;

    while (row != to_row || column != to_column) {
        if (!is_empty(board[row][column])) {
            return false;
        }
        row += row_step;
        column += column_step;
    }
    return true;
}


static bool pawn_can_move(
    const char board[BOARD_SIZE][BOARD_SIZE],
    Player player,
    int from_row,
    int from_column,
    int to_row,
    int to_column
)
{
    int row_delta = to_row - from_row;
    int column_delta = abs(to_column - from_column);
    int forward = player == PLAYER_WHITE ? -1 : 1;
    int starting_row = player == PLAYER_WHITE ? 6 : 1;

    if (column_delta == 0 && row_delta == forward) {
        return is_empty(board[to_row][to_column]);
    }
    if (column_delta == 0 && row_delta == 2 * forward && from_row == starting_row) {
        return is_empty(board[from_row + forward][from_column])
            && is_empty(board[to_row][to_column]);
    }
    if (column_delta == 1 && row_delta == forward) {
        return !is_empty(board[to_row][to_column]);
    }
    return false;
}


bool is_legal_move(
    const char board[BOARD_SIZE][BOARD_SIZE],
    Player player,
    int from_row,
    int from_column,
    int to_row,
    int to_column
)
{
    int row_delta;
    int column_delta;
    char piece;

    if (!is_inside_board(from_row, from_column)
        || !is_inside_board(to_row, to_column)
        || (from_row == to_row && from_column == to_column)) {
        return false;
    }

    piece = board[from_row][from_column];
    if (!player_owns_piece(piece, player)
        || same_side(piece, board[to_row][to_column])) {
        return false;
    }

    row_delta = abs(to_row - from_row);
    column_delta = abs(to_column - from_column);

    switch (tolower((unsigned char)piece)) {
    case 'k':
        return row_delta <= 1 && column_delta <= 1;
    case 'q':
        if (!(from_row == to_row || from_column == to_column
            || row_delta == column_delta)) {
            return false;
        }
        return path_is_clear(
            board, from_row, from_column, to_row, to_column
        );
    case 'r':
        if (!(from_row == to_row || from_column == to_column)) {
            return false;
        }
        return path_is_clear(
            board, from_row, from_column, to_row, to_column
        );
    case 'b':
        if (row_delta != column_delta) {
            return false;
        }
        return path_is_clear(
            board, from_row, from_column, to_row, to_column
        );
    case 'n':
        return (row_delta == 2 && column_delta == 1)
            || (row_delta == 1 && column_delta == 2);
    case 'p':
        return pawn_can_move(
            board, player, from_row, from_column, to_row, to_column
        );
    default:
        return false;
    }
}


bool move_piece(
    Board board,
    Player player,
    int from_row,
    int from_column,
    int to_row,
    int to_column
)
{
    char piece;

    if (!is_legal_move(
        board, player, from_row, from_column, to_row, to_column
    )) {
        return false;
    }

    piece = board[from_row][from_column];
    board[to_row][to_column] = piece;
    board[from_row][from_column] = EMPTY_SQUARE;

    if (piece == 'P' && to_row == 0) {
        board[to_row][to_column] = 'Q';
    } else if (piece == 'p' && to_row == BOARD_SIZE - 1) {
        board[to_row][to_column] = 'q';
    }
    return true;
}


bool has_king(const char board[BOARD_SIZE][BOARD_SIZE], Player player)
{
    char king = player == PLAYER_WHITE ? 'K' : 'k';
    int row;
    int column;

    for (row = 0; row < BOARD_SIZE; ++row) {
        for (column = 0; column < BOARD_SIZE; ++column) {
            if (board[row][column] == king) {
                return true;
            }
        }
    }
    return false;
}
