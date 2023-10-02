CC := gcc
CFLAGS := -Wall -Wextra -pedantic -ggdb -Wmultichar -g

test : build_test clean run

build_test : test.o word_manager.o screen_manager.o
	$(CC) $(CFLAGS) -o out $^

all : build clean run

build : main.o word_manager.o screen_manager.o game_loop.o
	$(CC) $(CFLAGS) -o duckytypes $^

run : 
	./duckytypes

clean :
	rm *.o