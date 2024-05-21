#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 10000

void print_word(const char* word, const char* input);
void play_game(
        char words[MAX_NUM_WORDS][MAX_WORD_LENGTH],
        int min_len,
        int max_len,
        int num_rounds);
void update_high_score(int score);