#include <stdio.h>
#include <stdlib.h>

#include "screen_manager.h"

void clear_screen() {
    printf("\33[2J\33[H");
}

void reset_line() {
    printf("\n\r\33[A\33[2K");

    // printf("\n");       // new line
    // printf("\r");    // carriage return
    // printf("\33[A");   // cursor up
    // printf("\33[2K");   // delete line
}

char*[] display_words(char *word_list[100], int list_size, int word_size, int count) {
    for (int i = 0; i < (count > list_size ? count : list_size); i++) {
        printf("%s ", word_list[i]);
    }
    printf("\n");
}