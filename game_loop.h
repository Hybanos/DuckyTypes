#include "consts.h"

// #include <termios.h>

struct testData {
    char word[WORD_SIZE * TEST_LENGTH];
    char test_data[WORD_SIZE * TEST_LENGTH];
    char test_string[WORD_SIZE * TEST_LENGTH];
};

struct testResult {
    int success_code;
    long start_time;
    long end_time;
    long dt;
    int raw_wpm;
    int wpm;
    int errors;
    int accuracy;
};

void prep_console(struct termios *, struct termios *);
void reset_console(struct termios *);
void main_loop(struct testData *, struct testResult *);