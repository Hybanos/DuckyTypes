CC := gcc
CFLAGS := -Wall -Wextra -pedantic -ggdb -Wmultichar -fno-stack-protector

test : build_test clean run

build_test : test.o word_manager.o screen_manager.o
	$(CC) $(CFLAGS) -o out $^

all : build clean run

build : main.o word_manager.o screen_manager.o
	$(CC) $(CFLAGS) -o out $^

run : 
	./out

clean :
	rm *.o