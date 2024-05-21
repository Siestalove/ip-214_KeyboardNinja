#include <ctype.h>
#include <math.h>

#include <lib/lib.h>

void print_word(const char* word, const char* input)
{
    clear();
    printw("%s\n%s", word, input);
    refresh();
}
void play_game(
        char words[MAX_NUM_WORDS][MAX_WORD_LENGTH],
        int min_len,
        int max_len,
        int num_rounds)
{
    char input[MAX_WORD_LENGTH];
    int i, len, score = 0, used[MAX_NUM_WORDS] = {0}, word_index;
    time_t start_time, end_time;
    float total_time = 0;
    int correct_words = 0;

    for (i = 0; i < num_rounds; i++) {
        start_time = time(NULL);
        do {
            word_index = rand() % MAX_NUM_WORDS;
            len = strlen(words[word_index]);
        } while (used[word_index] || len < min_len || len > max_len);
        used[word_index] = 1;
        print_word(words[word_index], "");

        int ch, pos = 0;
        while (1) {
            ch = getch();
            if (ch == KEY_BACKSPACE || ch == 127) {
                if (pos > 0) {
                    pos--;
                    input[pos] = '\0';
                }
            } else if (ch == KEY_ENTER || ch == '\n') {
                if (strcasecmp(input, words[word_index]) == 0) {
                    score++;
                    correct_words++;
                } else {
                    printw("Incorrect!\n");
                }
                break;
            } else if (isalpha(ch)) {
                if (pos < MAX_WORD_LENGTH - 1) {
                    input[pos] = ch;
                    pos++;
                    input[pos] = '\0';
                }
            }
            print_word(words[word_index], input);
        }
        end_time = time(NULL);
        total_time += difftime(end_time, start_time);
    }

    float accuracy = ((float)score / num_rounds) * 100;
    float f_score = (float)score / (total_time / 60);

    clear();
    printw("Точность: %.2f%%\n", accuracy);
    printw("Потраченное время: %.0f:%02.0f\n",
           total_time / 60,
           fmod(total_time, 60));
    printw("Твои слова в минуту: %.2f\n", f_score);
    printw("Правильно введенные слова: %d из %d\n", correct_words, num_rounds);
    printw("Дата конца: %s", ctime(&end_time));

    update_high_score(score);
}

void update_high_score(int f_score)
{
    int high_score = 0;
    FILE* fp = fopen("ninja_txt/highscore.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &high_score);
        fclose(fp);
    }

    if (f_score > high_score) {
        high_score = f_score;

        fp = fopen("ninja_txt/highscore.txt", "w");
        if (fp != NULL) {
            fprintf(fp, "%d", high_score);
            fclose(fp);
        }

        printw("Новый рекорд: %d!\n", high_score);
    } else {
        printw("Текущий рекорд: %d\n", high_score);
    }

    printw("\nНажмите любую кнопку для выхода");
    getch();
}