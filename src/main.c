#include "chess.h"

#include <stdio.h>
#include <stdlib.h>


static int read_menu_choice(void)
{
    char input[32];
    char *end = NULL;
    long choice;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 3;
    }

    choice = strtol(input, &end, 10);
    if (end == input || choice < 1 || choice > 3) {
        return 0;
    }
    return (int)choice;
}


int main(void)
{
    initialize_console();

    for (;;) {
        int choice;

        clear_console();
        printf("=================================\n");
        printf("          CONSOLE CHESS          \n");
        printf("=================================\n\n");
        printf("1. 게임 시작\n");
        printf("2. 도움말\n");
        printf("3. 종료\n\n");
        printf("선택: ");

        choice = read_menu_choice();
        if (choice == 1) {
            run_game();
        } else if (choice == 2) {
            show_help();
        } else if (choice == 3) {
            clear_console();
            printf("게임을 종료합니다.\n");
            return 0;
        } else {
            printf("1~3 사이의 숫자를 입력하세요.\n");
            wait_for_enter();
        }
    }
}
