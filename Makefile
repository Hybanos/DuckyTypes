CC := gcc
CFLAGS := -Wall -Wextra -pedantic -ggdb -Wmultichar

test : build_test clean run

build_test : test.o word_manager.o screen_manager.o
	$(CC) $(CFLAGS) -o out $^

all : _build clean run

build : _build clean

_build : main.o word_manager.o screen_manager.o game_loop.o config.o
	$(CC) $(CFLAGS) -o duckytypes $^
	
run : 
	./duckytypes

clean :
	rm *.o