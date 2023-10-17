#include "consts.h"

#include "word_manager.h"
#include "screen_manager.h"
#include "game_loop.h"
#include "config.h"

int main() {

    struct sconfig config;
    manage_config(&config);

    struct termios new_kbd_mode;
    struct termios g_old_kbd_mode;

    srand(time(NULL));
    
    struct testData data;
    data.test_string = calloc(sizeof(char), config.word_size * config.test_length);
    data.test_data = calloc(sizeof(char), config.word_size * config.test_length);
    data.word = calloc(sizeof(char), config.word_size * config.test_length);

    char *word_list = parse_file(&config);
    struct testResult res;

    prep_console(&new_kbd_mode, &g_old_kbd_mode);
    test(&data, &res, word_list, &config);

    free(word_list);
    reset_console(&g_old_kbd_mode);
    
    return EXIT_SUCCESS;
}