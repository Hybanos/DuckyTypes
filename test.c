#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>

#include "word_manager.h"

#define _XOPEN_SOURCE 700
 
int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}


int main() {

    srand(time(NULL));

    int const LIST_SIZE = 1500;
    int const WORD_SIZE = 100;

    char word_list[LIST_SIZE][WORD_SIZE];
    parse_file(word_list, LIST_SIZE, WORD_SIZE);

    char random_words[10][WORD_SIZE];
    select_random_words(word_list, LIST_SIZE, random_words, 10, WORD_SIZE);

    for (int i = 0; i < 50; i++) {
        printf("%s\n", random_words[i]);

        char word[100];
        int word_ptr = 0;

        int key;

        while (1) {
            key = getkey();
            if (key == 0x1B || key == 0x04 || key == ' ' || key == 'j') {
                return 0;
            } else {
                printf("%d\n", key);
            }
        }
    }

    return EXIT_SUCCESS;
}