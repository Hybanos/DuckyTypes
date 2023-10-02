#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "word_manager.h"
#include "screen_manager.h"
#include "game_loop.h"

int main() {

    struct termios new_kbd_mode;
    struct termios g_old_kbd_mode;
    prep_console(&new_kbd_mode, &g_old_kbd_mode);

    srand(time(NULL));

    int const LIST_SIZE = 1000;
    int const WORD_SIZE = 100;
    int const TEST_LENGTH = 20;

    char *word_list = calloc(LIST_SIZE, WORD_SIZE);
    parse_file(word_list, LIST_SIZE, WORD_SIZE);

    char *random_words = calloc(TEST_LENGTH, WORD_SIZE);
    select_random_words(word_list, LIST_SIZE, random_words, TEST_LENGTH, WORD_SIZE);

    char *word = calloc(TEST_LENGTH, WORD_SIZE);
    int word_ptr = 0;
    char *test_string = calloc(WORD_SIZE, TEST_LENGTH);
    int test_string_ptr = 0;
    int test_done = 0;
    char c = -1;

    clear_screen();
    int start_time = time(0);

    while (!test_done) {
        
        if (word_ptr == 1) start_time = (int) time(0);

        test_string_ptr = -1;

        /* TEST STRING BUILDING */
        for (int i = 0; i < TEST_LENGTH; i ++) {
            for (int j = 0; j < WORD_SIZE; j++) {
                test_string_ptr += 1;
                char curr = random_words[i * WORD_SIZE + j];
                if (curr == 0 || curr == 4 || curr == 13) {
                    test_string[test_string_ptr] = 32;
                    break;
                }
                test_string[test_string_ptr] = curr;
            }
        }
        test_string[test_string_ptr] = 0;

        goto_origin();
    
        /* SPELL CHECKER */
        for (int i = 0; i < WORD_SIZE * TEST_LENGTH; i ++) {

            char expected = test_string[i];
            char current = word[i];

            if (expected == 0 && word_ptr >= i) test_done = 1;
            if (expected == 0) break;

            if ((0b11000000 & test_string[i]) == 0b10000000 ) {
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
        if (c == 27) {
            // ESCAPE
            break;
        } else if (c == 127) {
            // BACKSPACE
            word_ptr -= 1;
            word[word_ptr] = 0;
        } else {
            // OTHER
            word[word_ptr] = c;
            word_ptr += 1;
        }
    }

    reset_color();
    reset_console(&g_old_kbd_mode);

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

    free(word_list);
    free(random_words);
    free(test_string);
    free(word);

    return EXIT_SUCCESS;
}