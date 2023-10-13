#include "consts.h"

#include "config.h"
#include "game_loop.h"
#include "screen_manager.h"
#include "word_manager.h"

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

int get_next_space(struct testData *data, int word_ptr) {
    for (int i = word_ptr; i < strlen(data->test_string); i++) {
        if (data->test_string[i] == 32) return i;
    }
    return strlen(data->test_string);
}

int get_prev_space(struct testData *data, int word_ptr) {
    for (int i = word_ptr - 1; i > 0; i--) {
        if (data->test_string[i] == 32 && word_ptr-1 != i) return i;
    }
    return -1;
}

int count_char(char *string, char c) {
    int cpt = 0;
    for (int i = 0; i < strlen(string); i ++) {
        if (string[i] == c) cpt += 1;
    }
    return cpt;
}

void test(struct testData *data, struct testResult *res, char *word_list, struct sconfig *config) {

    char c = 0;

    while (1) {
        do {
            select_random_words(word_list, data, config);
            printf(word_list);

            main_loop(data, res, config);
        } while (res->success_code == TEST_RESTART);

        switch (res->success_code) {
            case TEST_ABORT:
                display_abort();
                return;

            case TEST_END:
                display_results(res, config);
                break;
        }

        while (1) {
            read(0, &c, 1);
            if (c == 27) return;
            if (c == 9) break;
        }
    }
}

void main_loop(struct testData *data, struct testResult *res, struct sconfig *config) {
    int word_ptr = 0;
    int test_string_ptr = -1;
    int test_done = 0;
    char c = -1;
    res->success_code = TEST_END;
    clear_screen();
    res->start_time = time(0);

    /* TEST STRING BUILDING */
    for (int i = 0; i < config->test_length; i ++) {
        for (int j = 0; j < config->word_size; j++) {
            test_string_ptr += 1;
            char curr = data->test_data[i * config->word_size + j];
            if (curr == 0 || curr == 4 || curr == 13) {
                data->test_string[test_string_ptr] = 32;
                break;
            }
            data->test_string[test_string_ptr] = curr;
        }
    }

    data->test_string[test_string_ptr] = 0;

    char *display_word = malloc(config->word_size * config->test_length * 50);

    while (!test_done) {
        memset(display_word, 0, config->word_size * config->test_length * 50);

        if (word_ptr == 1) res->start_time = (long) time(0);
        goto_origin();
    
        /* SPELL CHECKER */
        for (int i = 0; i < config->word_size * config->test_length; i ++) {

            char expected = data->test_string[i];
            char current = data->word[i];

            if (expected == 0 && word_ptr >= i ) test_done = 1; 
            if (expected == 0) break;

            if ((0b11000000 & expected) == 0b10000000 ) {
                int len = strlen(display_word);
                display_word[len] = expected;
                display_word[len + 1] = 0;
                continue;
            }

            if (i == word_ptr) strcat(display_word, "\33[48;2;90;90;90m");
            else strcat(display_word, "\33[0m");

            if (i < word_ptr) {
                if (current != 0 && current != 4 && current != 13) {
                    if (expected == current) {
                        // strcat(display_word, "\33[38;2;150;150;150m");
                        strcat(display_word, "\33[1;30m");
                    } else {
                        strcat(display_word, "\33[38;2;200;50;50m");
                    }
                }

            } 
            if (i == word_ptr) {strcat(display_word, "\33[38;2;255;255;255m");}

            int len = strlen(display_word);
            display_word[len] = expected;
            display_word[len + 1] = 0;

        }
        display_test(display_word, config);

        if (test_done) break;
        read(0, &c, 1);

        /* PARSE WRITTEN */
        switch (c) {
            case 27: // ESCAPE
                res->success_code = TEST_ABORT;
                free(display_word);
                return;

            case 127: // BACKSPACE
                if (!word_ptr) break;
                if ((0b11000000 & data->word[word_ptr - 1]) == 0b010000000) word_ptr -= 2;
                else word_ptr -= 1;
                break;    

            case 9: // TAB
                res->success_code = TEST_RESTART;
                free(display_word);
                return;   

            case 32: // SPACE
                if (data->word[word_ptr - 1] == ' ') break;
                for (int i = word_ptr; i < get_next_space(data, word_ptr); i++) {
                    data->word[word_ptr] = c;
                    word_ptr += 1;
                }
                data->word[word_ptr] = c;
                word_ptr += 1;
                break;

            case 8: // CTRL + BACKSPACE
                word_ptr = get_prev_space(data, word_ptr) + 1;
                break;
                
            default:
                data->word[word_ptr] = c;
                word_ptr += 1;
        }
    }
    free(display_word);
    calculate_results(data, res);
    res->success_code = TEST_END;
}

void calculate_results(struct testData *data, struct testResult *res) {
    res->end_time = (long) time(0);
    res->dt = res->end_time - res->start_time;
    res->raw_wpm = strlen(data->word) / 5 * 60 / res->dt;

    res->errors = 0;
    for (int i = 0; i < (int) strlen(data->word) - 1; i++) {
        if (data->word[i] != data->test_string[i] && data->test_string[i] != 32) res->errors += 1;
    }

    res->accuracy = 0;
    if (res->errors) {
        res->accuracy = 100 - (float) res->errors /  (strlen(data->word) - count_char(data->test_string, ' ')) * 100;
    }
    else {
        res->accuracy = 100;
    }
    res->wpm = res->raw_wpm * res->accuracy / 100;
}

