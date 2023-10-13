
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
    prep_console(&new_kbd_mode, &g_old_kbd_mode);

    srand(time(NULL));
    hide_cursor();
    
    struct testData data; 
    data.test_string = calloc(sizeof(char), config.word_size * config.test_length);
    data.test_data = calloc(sizeof(char), config.word_size * config.test_length);
    data.word = calloc(sizeof(char), config.word_size * config.test_length);

    char *word_list = calloc(config.list_size, config.word_size);
    parse_file(word_list, &config);
    struct testResult res;

    test(&data, &res, word_list, &config);

    free(word_list);
    reset_console(&g_old_kbd_mode);
    
    enable_cursor();
    
    return EXIT_SUCCESS;
}