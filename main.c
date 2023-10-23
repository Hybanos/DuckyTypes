#include "consts.h"

#include "word_manager.h"
#include "screen_manager.h"
#include "game_loop.h"
#include "config.h"

void a();

int main() {

    struct sconfig config;
    manage_config(&config);

    struct termios new_kbd_mode;
    struct termios g_old_kbd_mode;

    srand(config.seed);

    struct testData data;
    data.test_string = calloc(sizeof(char), config.word_size * config.test_length);
    data.test_data = calloc(sizeof(char), config.word_size * config.test_length);
    data.word = calloc(sizeof(char), config.word_size * config.test_length);

    char *word_list = parse_file(&config);
    struct testResult res;

    prep_console(&new_kbd_mode, &g_old_kbd_mode);
    test(&data, &res, word_list, &config);
    reset_console(&g_old_kbd_mode);

    free(word_list);
    free(&config);
    free(data.test_string);
    free(data.test_data);
    free(data.word);
    free(config.path);
    free(config.config_path);
    a();

    return EXIT_SUCCESS;
}

void a() {

}