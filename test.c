#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

#include "word_manager.h"
#include "screen_manager.h"

int main() {

    char c;
    struct termios new_kbd_mode;
    struct termios g_old_kbd_mode;

    tcgetattr (0, &g_old_kbd_mode);
    memcpy (&new_kbd_mode, &g_old_kbd_mode, sizeof (struct termios));

    new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    tcsetattr (0, TCSANOW, &new_kbd_mode);



    srand(time(NULL));

    int const LIST_SIZE = 1500;
    int const WORD_SIZE = 100;

    char word_list[LIST_SIZE][WORD_SIZE];
    parse_file(word_list, LIST_SIZE, WORD_SIZE);

    char random_words[50][WORD_SIZE];
    select_random_words(word_list, LIST_SIZE, random_words, 30, WORD_SIZE);



    char word[100];
    int word_ptr = 0;
    for (int i = 0; i < 30; i++) {
        clear_screen();
        for (int i = 0; i < 5; i++) {
            printf("%s", random_words[i]);
        }
        printf("\n");



        for (int i = 0; i < WORD_SIZE; i++) {
            word[i] = 0;
        }
        word_ptr = 0;
        c = -1;
        while (c != 32) {


            read(0, &c, 1);

            if ((int)c == 127) {
                word_ptr -= 1;
                word[word_ptr] = 0;
            } else {
                word[word_ptr] = c;
                word_ptr += 1;
            }

            printf("%s", word);
            reset_line();
        
        }
    }


    tcsetattr (0, TCSANOW, &g_old_kbd_mode);
    return EXIT_SUCCESS;
}