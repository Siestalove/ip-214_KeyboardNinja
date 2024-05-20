#include <ctype.h>
#include <math.h>

void print_word(const char* word, const char* input)
{
    clear();
    printw("%s\n%s", word, input);
    refresh();
}