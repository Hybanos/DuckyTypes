#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <time.h>  
#include <string.h> 

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
    int const TEST_LENGTH = 30;

    char word_list[LIST_SIZE][WORD_SIZE];
    parse_file(word_list, LIST_SIZE, WORD_SIZE);

    char random_words[TEST_LENGTH][WORD_SIZE];
    select_random_words(word_list, LIST_SIZE, random_words, TEST_LENGTH, WORD_SIZE);



    char word[100];
    int word_ptr = 0;
    char test_string[WORD_SIZE * TEST_LENGTH];
    int test_string_ptr = 0;
    int words_index = 0;
    int test_done = 0;
    word_ptr = 0;
    c = -1;
    
    clear_screen();
    // rgb_text(255, 50, 50);

    int start_time;

    while (!test_done) {
        
        if (word_ptr == 1) start_time = (int) time(0);

        test_string_ptr = -1;

        /* TEST STRING BUILDING */
        for (int i = 0; i < TEST_LENGTH; i ++) {
            for (int j = 0; j < WORD_SIZE; j++) {
                test_string_ptr += 1;
                char curr = random_words[i][j];
                if (curr == 0 || curr == 4 || curr == 13) {
                    test_string[test_string_ptr] = 32;
                    break;
                }
                test_string[test_string_ptr] = curr;
            }
        }
        test_string[test_string_ptr] = 0;

        // clear_screen();
        goto_origin();
    
        /* SPELL CHECKER */
        for (int i = 0; i < WORD_SIZE * TEST_LENGTH; i ++) {

            char expected = test_string[i];
            char current = word[i];

            if (expected == 0 && word_ptr >= i) test_done = 1;
            if (expected == 0) break;
            
            if ((192 & test_string[i]) == 128 ) {
                printf("%c", expected);
                continue;
            }

            if (i == word_ptr) {
                rgb_background(90, 90, 90);
            } else {
                // reset_background();
                reset_color();
            }

            if (i < word_ptr) {
                if (current != 0 & current != 4 && current != 13) {
                    if (expected == current) {
                        rgb_text(150, 150, 150);
                    } else {
                        rgb_text(200, 50, 50);
                    }
                }

            } else {
                rgb_text(255, 255, 255);
            }


            printf("%c", expected);
        }
        reset_color();
        printf("\n");


        read(0, &c, 1);


        /* PARSE WRITTEN */
        if (c == 32) {
            words_index += 1;
        }

        if (c == 127) {
            word_ptr -= 1;
            if (word[word_ptr] == 32) {
                words_index -= 1;
            }
            word[word_ptr] = 0;
        } else {
            word[word_ptr] = c;
            word_ptr += 1;
        }
    }
    reset_color();

    int dt = ((int) time(0)) - start_time;
    int raw = strlen(word) / 5 * 60 / dt;

    int errors = 0;
    for (int i = 0; i < strlen(word) - 1; i++) {
        if (word[i] != test_string[i]) errors += 1; 
    }

    int accuracy = 0;
    if (errors) {
        accuracy = 100 - (float) errors /  strlen(word) * 100;
    }
    else {
        accuracy = 100;
    }
    int wpm = raw * accuracy / 100;

    printf("Done in %d seconds!\n", dt);
    printf("%i Words per minute, (%i raw)\n", wpm, raw);
    printf("%i typos, (%d%% accuracy)\n", errors, accuracy);

    tcsetattr(0, TCSANOW, &g_old_kbd_mode);
    return EXIT_SUCCESS;
}