
#include "consts.h"

#include "word_manager.h"
#include "screen_manager.h"
#include "game_loop.h"
#include "config.h"

int main() {

    manage_config();

    hide_cursor();

    struct termios new_kbd_mode;
    struct termios g_old_kbd_mode;
    prep_console(&new_kbd_mode, &g_old_kbd_mode);

    srand(time(NULL));

    struct testData data; 
    char *word_list = calloc(LIST_SIZE, WORD_SIZE);
    parse_file(word_list, LIST_SIZE, WORD_SIZE);
    struct testResult res;

    test(&data, &res, word_list);

    free(word_list);
    reset_console(&g_old_kbd_mode);
    
    enable_cursor();
    
    return EXIT_SUCCESS;
}