#include "consts.h"

#include "screen_manager.h"

void clear_screen() {
    printf("\33[2J\33[H");
}

void goto_origin() {
    printf("\33[0;0H");
}

void reset_line() {
    printf("\n\r\33[A\33[2K");
}

void reset_color() {
    printf("\33[0m");
}

void rgb_text(int r, int g, int b) {
    printf("\33[38;2;%d;%d;%dm", r, g, b);
}

void rgb_background(int r, int g, int b) {
    printf("\33[48;2;%d;%d;%dm", r, g, b);
}