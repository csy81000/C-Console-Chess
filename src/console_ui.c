#include "chess.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


static const WORD DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;


void initialize_console(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleTitleW(L"Console Chess");
}


void clear_console(void)
{
    system("cls");
}


void wait_for_enter(void)
{
    char input[8];

    printf("계속하려면 Enter 키를 누르세요...");
    (void)fgets(input, sizeof(input), stdin);
}


static WORD square_color(char piece, bool highlighted, bool dark_square)
{
    WORD background;
    WORD foreground;

    if (highlighted) {
        background = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    } else if (dark_square) {
        background = BACKGROUND_BLUE | BACKGROUND_GREEN;
    } else {
        background = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    }

    if (isupper((unsigned char)piece)) {
        foreground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
            | FOREGROUND_INTENSITY;
    } else if (islower((unsigned char)piece)) {
        foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    } else {
        foreground = 0;
    }
    return background | foreground;
}


void draw_board(
    const char board[BOARD_SIZE][BOARD_SIZE],
    Player player,
    int selected_row,
    int selected_column
)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    int row;
    int column;

    SetConsoleTextAttribute(output, DEFAULT_COLOR);
    printf("      1  2  3  4  5  6  7  8\n");
    printf("    +------------------------+\n");

    for (row = 0; row < BOARD_SIZE; ++row) {
        printf(" %c  |", 'A' + row);
        for (column = 0; column < BOARD_SIZE; ++column) {
            bool highlighted = selected_row >= 0
                && is_legal_move(
                    board,
                    player,
                    selected_row,
                    selected_column,
                    row,
                    column
                );
            char piece = board[row][column];

            SetConsoleTextAttribute(
                output,
                square_color(piece, highlighted, (row + column) % 2 != 0)
            );
            printf(" %c ", piece == EMPTY_SQUARE ? ' ' : piece);
        }
        SetConsoleTextAttribute(output, DEFAULT_COLOR);
        printf("|\n");
    }

    printf("    +------------------------+\n");
    printf("대문자: 백 / 소문자: 흑\n");
}


void show_help(void)
{
    clear_console();
    printf("[게임 방법]\n\n");
    printf("- 백(대문자)이 먼저 시작하며 두 플레이어가 번갈아 둡니다.\n");
    printf("- 위치는 행 문자와 열 숫자를 붙여 입력합니다. 예: G1, E4\n");
    printf("- 말을 고르면 이동 가능한 칸이 초록색으로 표시됩니다.\n");
    printf("- 상대 킹을 잡으면 게임이 끝납니다.\n");
    printf("- 폰이 마지막 행에 도착하면 자동으로 퀸으로 승급합니다.\n");
    printf("- 좌표 입력 중 Q를 누르면 메인 메뉴로 돌아갑니다.\n\n");
    printf("이 수업 프로젝트 버전은 체크/체크메이트, 캐슬링, 앙파상을\n");
    printf("구현하지 않은 간소화된 로컬 2인용 체스입니다.\n\n");
    wait_for_enter();
}
