#include <stdio.h>
#include <stdlib.h>

#include "word_manager.h"

void parse_file(char *word_list, int list_size, int word_size) {
    FILE *f_ptr;
    f_ptr = fopen("words_fr.txt", "r");
    
    char word[word_size];

    for (int i = 0; i < list_size; i++) {
        fgets(word, word_size, f_ptr);
        for (int j = 0; j < word_size - 1; j++) {
            if (word[j] == '\n') {
                word_list[i * word_size + j] = EOF;
            } else {
                word_list[i * word_size + j] = word[j];
            }
        }
    }

    fclose(f_ptr);
}

void select_random_words(char *input_list, int input_size, char* output_list, int output_size, int word_size) {
    for (int i = 0; i < output_size; i++) {
        int index = rand() % input_size;
        
        for (int j = 0; j < word_size; j++) {
            output_list[i * word_size + j] = input_list[index * word_size + j];
        }
    }
}