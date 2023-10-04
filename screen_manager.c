#include "game_loop.h"

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

char* mult_ch(char c, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
}

void display_test(char *str) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    char *output = calloc(WORD_SIZE, TEST_LENGTH * 50);

    int average_letterspword = 6;

    int side_spacing =  0.25 * w.ws_col;
    int top_spacing = (w.ws_row - TEST_LENGTH / average_letterspword) / 2;
    int wpl = (w.ws_col - 2 * side_spacing) / average_letterspword;

    char *side = calloc(1, side_spacing);
    for (int i = 0; i < side_spacing; i++) {
        strcat(side, " ");
    }

    int str_index = 0;
    int out_index = 0;

    int curr_spaces = 0;

    for (int i = 0; i < top_spacing; i++) {
        strcat(output, "\n");
        out_index += 1;
    }

    while (1) {
        strcat(output, "\33[0m");
        strcat(output, side);
        out_index += 4;
        out_index += side_spacing;
        curr_spaces = 0;
        while (curr_spaces < wpl) {
            if (str_index >= strlen(str)) break;
            output[out_index] = str[str_index];
            out_index += 1;
            str_index += 1;
            if (str[str_index - 1] == ' ') {
                curr_spaces += 1;
            };
        }
        if (str_index >= strlen(str)) break;
        strcat(output, "\n");
        out_index += 1;
    }

    for (int i = 0; i < top_spacing / 2; i++) {
        strcat(output, "\n");
        out_index += 1;
    }

    printf(output);
    printf("\33[0m");

    free(output);
    free(side);
}

void display_results(struct testResult *res) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    mult_ch(' ', (w.ws_col - 20) / 2);
    printf("Done in %ld seconds!\n", res->dt);

    mult_ch(' ', (w.ws_col - 28) / 2);
    printf("%i words per minute (%i raw)\n", res->wpm, res->raw_wpm);
    
    mult_ch(' ', (w.ws_col - 21) / 2);
    printf("%i typos (%d%% accuracy)\n", res->errors, res->accuracy);

        mult_ch('\n', w.ws_row / 8);

    mult_ch(' ', (w.ws_col - 41) / 2);
    printf("Press [Tab] to restart and [Esc] to quit.\n\n");
}

void display_abort() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    mult_ch(' ', (w.ws_col - 13) / 2);
    printf("Test Aborted.\n\n");
}

void hide_cursor() {
    printf("\e[?25l");
}

void enable_cursor() {
    printf("\e[?25h");
}