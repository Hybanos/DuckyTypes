#ifndef TERMIOS_H
#define TERMIOS_H
#include <termios.h>
#include <string.h>
#include <unistd.h>
#endif

#include "game_loop.h"

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

void main_loop() {

}

