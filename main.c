
#include "consts.h"

#include "word_manager.h"
#include "screen_manager.h"
#include "game_loop.h"

int main() {

    struct termios new_kbd_mode;
    struct termios g_old_kbd_mode;
    prep_console(&new_kbd_mode, &g_old_kbd_mode);

    srand(time(NULL));

    struct testData data;
    char *word_list = calloc(LIST_SIZE, WORD_SIZE);
    parse_file(word_list, LIST_SIZE, WORD_SIZE);
    struct testResult res;

    do {
        select_random_words(word_list, LIST_SIZE, data.test_data, TEST_LENGTH, WORD_SIZE);
        main_loop(&data, &res);
    } while (res.success_code == TEST_RESTART);

    switch (res.success_code) {
        case TEST_ABORT:
            display_abort();
            break;

        case TEST_END:
            display_results(&res);
            break;    
    }

    free(word_list);
    reset_console(&g_old_kbd_mode);

    return EXIT_SUCCESS;
}