#include <stdio.h>
#include <stdlib.h>

void random_line(char* word_ptr) {
    read_line(word_ptr, rand() % 1500);
}

void read_line(char* word_ptr, int n) {
    FILE *f_ptr;
    f_ptr = fopen("words_fr.txt", "r");

    for (int i = 0; i < n; i++) {
        fgets(word_ptr, 100, f_ptr);
    }
    fclose(f_ptr);
}

void main() {

    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        char word[100];
        random_line(word);
        printf("%s", word);
    }
}