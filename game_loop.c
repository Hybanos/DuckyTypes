#include <stdio.h>
#include <stdlib.h>

#include <termios.h>
#include <string.h>
#include <unistd.h>

#include "game_loop.h"

void prep_console(struct termios *new_kbd_mode, struct termios *g_old_kbd_mode) {
    tcgetattr (0, g_old_kbd_mode);
    memcpy(new_kbd_mode, g_old_kbd_mode, sizeof (struct termios));

    new_kbd_mode->c_lflag &= ~(ICANON | ECHO);
    new_kbd_mode->c_cc[VTIME] = 0;
    new_kbd_mode->c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, new_kbd_mode);
}

void reset_console(struct termios *g_old_kbd_mode) {
    tcsetattr(0, TCSANOW, g_old_kbd_mode);
}

void main_loop(struct testData data, struct testResult res) {
    int word_ptr = 0;
    int test_string_ptr = 0;
    int test_done = 0;
    char c = -1;
    res.success_code = TEST_END;

    clear_screen();
    int start_time = time(0);

    while (!test_done) {
        if (word_ptr == 1) res.start_time = (long) time(0);
        test_string_ptr = -1;

        /* TEST STRING BUILDING */
        for (int i = 0; i < TEST_LENGTH; i ++) {
            for (int j = 0; j < WORD_SIZE; j++) {
                test_string_ptr += 1;
                char curr = data.test_data[i * WORD_SIZE + j];
                if (curr == 0 || curr == 4 || curr == 13) {
                    data.test_string[test_string_ptr] = 32;
                    break;
                }
                data.test_string[test_string_ptr] = curr;
            }
        }

        data.test_string[test_string_ptr] = 0;
        goto_origin();
    
        /* SPELL CHECKER */
        for (int i = 0; i < WORD_SIZE * TEST_LENGTH; i ++) {

            char expected = data.test_string[i];
            char current = data.word[i];

            if (expected == 0 && word_ptr >= i ) test_done = 1; 
            if (expected == 0) break;

            if ((0b11000000 & data.test_string[i]) == 0b10000000 ) {
                printf("%c", expected);
                continue;
            }

            if (i == word_ptr) rgb_background(90, 90, 90);
            else reset_color();
            
            if (i < word_ptr) {
                if (current != 0 && current != 4 && current != 13) {
                    if (expected == current) {
                        rgb_text(150, 150, 150);
                    } else {
                        rgb_text(200, 50, 50);
                    }
                }

            } else rgb_text(255, 255, 255);
            
            printf("%c", expected);
        }
        reset_color();
        printf("\n");

        if (test_done) break;

        read(0, &c, 1);

        /* PARSE WRITTEN */
        if (c == 27) {
            // ESCAPE
            res.success_code = TEST_ABORT;
            break;
        } else if (c == 127) {
            // BACKSPACE
            word_ptr -= 1;
            data.word[word_ptr] = 0;
        } else {
            // OTHER
            data.word[word_ptr] = c;
            word_ptr += 1;
        }
    }

    reset_color();

    void calculate_results(data, res);
    
}

void calculate_results(struct testData data, struct testResult res) {
    res.end_time = (long) time(0);
    res.dt = res.end_time - res.start_time;
    res.raw_wpm = strlen(data.word) / 5 * 60 / res.dt;

    res.errors = 0;
    for (int i = 0; i < (int) strlen(data.word) - 1; i++) {
        if (data.word[i] != data.test_string[i]) res.errors += 1; 
    }

    res.accuracy = 0;
    if (res.errors) {
        res.accuracy = 100 - (float) res.errors /  strlen(data.word) * 100;
    }
    else {
        res.accuracy = 100;
    }
    int wpm = res.raw_wpm * res.accuracy / 100;
}

void display_results(struct testResult res) {

    printf("Done in %ld seconds!\n", res.dt);
    printf("%i Words per minute, (%i raw)\n", res.wpm, res.raw_wpm);
    printf("%i typos, (%d%% accuracy)\n", res.errors, res.accuracy);

}
