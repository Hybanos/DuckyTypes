#include <termios.h>

void prep_console(struct termios *, struct termios *);
void reset_console(struct termios *);