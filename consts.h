#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define WORD_SIZE 100
#define TEST_LENGTH 20
#define LIST_SIZE 1500

#define TEST_END 1
#define TEST_ABORT 2
#define TEST_RESTART 3