CC := gcc
CFLAGS := -Wall -Wextra -pedantic -ggdb -Wmultichar

all : _build clean run

build : _build clean

_build : main.o word_manager.o screen_manager.o game_loop.o config.o
	$(CC) $(CFLAGS) -o duckytypes $^

run : 
	./duckytypes

clean :
	rm *.o