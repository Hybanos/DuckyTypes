#define WORD_SIZE 100
#define TEST_LENGTH 20
#define LIST_SIZE 1500

#include <termios.h>

void prep_console(struct termios *, struct termios *);
void reset_console(struct termios *);

struct testData {
    char *word[WORD_SIZE];
    char *test_data[WORD_SIZE * TEST_LENGTH];
    char *test_string[WORD_SIZE * TEST_LENGTH];
};

struct testResult {
    int success_code;
    int time;

};