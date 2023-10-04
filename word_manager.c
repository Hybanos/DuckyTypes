#include "consts.h"

#include "word_manager.h"

void parse_file(char *word_list, int list_size, int word_size) {
    FILE *f_ptr;
    f_ptr = fopen("words_fr.txt", "r");
    
    char *word = calloc(word_size, 1);

    for (int i = 0; i < list_size; i++) {
        fgets(word, word_size, f_ptr);
        // printf("%s\n", word);
        
        for (int j = 0; j < word_size; j++) {
            if (word[j] == '\n') {
                word_list[i * word_size + j] = 0x0;
            } else {
                word_list[i * word_size + j] = word[j];
            }
        }
    }

    free(word);
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