#include "consts.h"

#include "config.h"
#include "game_loop.h"
#include "word_manager.h"

void parse_file(char *word_list, struct sconfig *config) {
    char *full_path = calloc(sizeof(char), 255);

    strcat(full_path, config->path);
    strcat(full_path, config->file_name);

    printf("words : %s\n\n", full_path);

    FILE *f_ptr;
    f_ptr = fopen(full_path, "r");
    free(full_path);
    
    char *word = calloc(config->word_size, 1);

    for (int i = 0; i < config->list_size; i++) {
        fgets(word, config->word_size, f_ptr);
        // printf("%s\n", word);
        
        for (int j = 0; j < config->word_size; j++) {
            if (word[j] == '\n') {
                word_list[i * config->word_size + j] = 0x0;
            } else {
                word_list[i * config->word_size + j] = word[j];
            }
        }
    }

    free(word);
    fclose(f_ptr);
}

void select_random_words(char *input_list, struct testData *data, struct sconfig *config) {
    for (int i = 0; i < config->test_length; i++) {
        int index = rand() % config->list_size;

        for (int j = 0; j < config->word_size; j++) {
            data->test_data[i * config->word_size + j] = input_list[index * config->word_size + j];
        }
    }
}