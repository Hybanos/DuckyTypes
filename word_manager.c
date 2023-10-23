#include "consts.h"

#include "config.h"
#include "game_loop.h"
#include "word_manager.h"

char * parse_file(struct sconfig *config) {

    char *full_path = calloc(sizeof(char), 255);

    strcat(full_path, config->path);
    strcat(full_path, "words/");

    DIR *dir = opendir(full_path);  
    if (!dir) {
        mkdir(full_path, 0700);
    }

    strcat(full_path, config->file_name);

    FILE *f_ptr;
    f_ptr = fopen(full_path, "r");
    puts(full_path);
    if (!f_ptr) {
        printf("couldn't find word file help\n");
        exit(EXIT_FAILURE);
    }
    free(full_path);

    int lines = 0;
    int ch = 0;
    while(!feof(f_ptr)) {
        ch = fgetc(f_ptr);
        if(ch == '\n') {
            lines++;
        }
    }

    rewind(f_ptr);

    config->list_size = lines;
    char * word_list = calloc(sizeof(char), config->list_size * config->word_size);
    
    char *word = calloc(config->word_size, 1);

    for (int i = 0; i < config->list_size; i++) {
        fgets(word, config->word_size, f_ptr);
        puts(word);
        
        for (int j = 0; j < config->word_size; j++) {
            if (word[j] == '\n') {
                word_list[i * config->word_size + j] = 0;
            } else {
                word_list[i * config->word_size + j] = word[j];
            }
        }
    }
    
    free(dir);
    free(word);
    fclose(f_ptr);
    return word_list;
}

void select_random_words(char *input_list, struct testData *data, struct sconfig *config) {
    for (int i = 0; i < config->test_length; i++) {
        int index = rand() % config->list_size;

        for (int j = 0; j < config->word_size; j++) {
            data->test_data[i * config->word_size + j] = input_list[index * config->word_size + j];;
        }
    }
}