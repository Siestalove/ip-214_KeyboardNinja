#include <lib/lib.h>

int main(void)
{
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(2));
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
    char difficulty;
    int num_words = 0;
    initscr();
    FILE* fp = fopen("ninja_txt/words.txt", "r");
    if (fp == NULL) {
        printw("Ошибка в открытии файла\n");
        refresh();
        endwin();
        exit(1);
    }
    while (fgets(words[num_words], MAX_WORD_LENGTH, fp) != NULL) {
        int len = strlen(words[num_words]);
        if (words[num_words][len - 1] == '\n') {
            words[num_words][len - 1] = '\0';
        }
        num_words++;
    }
    fclose(fp);
    srand(time(NULL));
    do {
        clear();
        printw("Выберите сложность:\n");
        printw("1) Лёгкая (длина слов 3-5)\n");
        printw("2) Средняя (длина слов 6-8)\n");
        printw("3) Сложная (длина слов 9-12)\n");
        printw("4) Невозможная (длина слов 13+)\n");
        printw("5) Выйти\n");
        refresh();
        difficulty = getch();
        switch (difficulty) {
        case '1':
            play_game(words, 3, 5, 25);
            break;
        case '2':
            play_game(words, 6, 8, 25);
            break;
        case '3':
            play_game(words, 9, 12, 25);
            break;
        case '4':
            play_game(words, 13, MAX_WORD_LENGTH, 25);
            break;
        case '5':
            break;
        default:
            printw("Некорректный выбор\n");
            break;
        }
        if (difficulty >= '1' && difficulty <= '4') {
            printw("\nНажмите любую кнопку для продолжения\n");
            refresh();
            getch();
        }
    } while (difficulty != '5');
    endwin();
    return 0;
}