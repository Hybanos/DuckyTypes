#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <dirent.h>

// #define LIST_SIZE 1500
// #define WORD_SIZE 100
// #define TEST_LENGTH 25

#define TEST_END 1
#define TEST_ABORT 2
#define TEST_RESTART 3