#include "consts.h"

struct testData {
    char *word;
    char *test_data;
    char *test_string;
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
void main_loop(struct testData *, struct testResult *, struct sconfig *);
void test(struct testData *, struct testResult *, char *, struct sconfig *);