#include "chess.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>


void reset_board(Board board)
{
    static const Board initial_board = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    memcpy(board, initial_board, sizeof(initial_board));
}


bool parse_position(const char *input, int *row, int *column)
{
    const char *cursor = input;
    char row_letter;
    int column_number;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }
    row_letter = (char)toupper((unsigned char)*cursor);
    if (row_letter == '\0') {
        return false;
    }
    ++cursor;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }
    if (*cursor < '1' || *cursor > '8') {
        return false;
    }
    column_number = *cursor - '0';
    ++cursor;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }
    if (*cursor != '\0' || row_letter < 'A' || row_letter > 'H') {
        return false;
    }

    *row = row_letter - 'A';
    *column = column_number - 1;
    return true;
}


static bool read_position(const char *prompt, int *row, int *column)
{
    char input[64];

    for (;;) {
        printf("%s (예: G1, Q: 메뉴): ", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return false;
        }
        if (toupper((unsigned char)input[0]) == 'Q') {
            return false;
        }
        if (parse_position(input, row, column)) {
            return true;
        }
        printf("A1부터 H8 사이의 좌표를 입력하세요.\n");
    }
}


int run_game(void)
{
    Board board;
    Player current_player = PLAYER_WHITE;

    reset_board(board);

    for (;;) {
        int from_row;
        int from_column;
        int to_row;
        int to_column;
        const char *player_name = current_player == PLAYER_WHITE
            ? "백(대문자)" : "흑(소문자)";

        clear_console();
        draw_board(board, current_player, -1, -1);
        printf("\n%s 차례입니다.\n", player_name);

        if (!read_position("이동할 말", &from_row, &from_column)) {
            return 0;
        }
        if (!player_owns_piece(board[from_row][from_column], current_player)) {
            printf("현재 플레이어의 말을 선택하세요.\n");
            wait_for_enter();
            continue;
        }

        clear_console();
        draw_board(board, current_player, from_row, from_column);
        printf("\n초록색 칸으로 이동할 수 있습니다.\n");
        if (!read_position("이동할 위치", &to_row, &to_column)) {
            continue;
        }
        if (!move_piece(
            board,
            current_player,
            from_row,
            from_column,
            to_row,
            to_column
        )) {
            printf("해당 위치로 이동할 수 없습니다.\n");
            wait_for_enter();
            continue;
        }

        if (!has_king(
            board,
            current_player == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE
        )) {
            clear_console();
            draw_board(board, current_player, -1, -1);
            printf("\n%s 승리!\n", player_name);
            wait_for_enter();
            return 0;
        }

        current_player = current_player == PLAYER_WHITE
            ? PLAYER_BLACK : PLAYER_WHITE;
    }
}
