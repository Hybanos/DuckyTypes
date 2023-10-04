#include "consts.h"

void clear_screen();
void reset_line();
void rgb_text(int, int, int);
void rgb_background(int, int, int);
void reset_color();
void goto_origin();
void display_test(char *);
void display_results(struct testResult *);
void display_abort();
void hide_cursor();
void enable_cursor();