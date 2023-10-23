#include <unistd.h>

#include "config.h"
#include "consts.h"

void get_path(struct sconfig *config) {
    config->path = calloc(sizeof(char), 255);
    readlink("/proc/self/exe", config->path, 255);

    for (int i = strlen(config->path); i > 0; i --) {
        if (config->path[i - 1] == '/') {
            config->path[i] = 0;
            break;
        }
    }
    
    config->config_path = calloc(sizeof(char), 255);
    strcat(config->config_path, config->path);
    strcat(config->config_path, "conf.conf");
    // printf("%s\n", config->path);
}

void create_config(struct sconfig *config) {
    FILE *fptr;

    fptr = fopen(config->config_path, "w");
    fprintf(fptr, "# File to read words from.\n");
    fprintf(fptr, "word_list_file=english_1k.txt\n\n");

    fprintf(fptr, "# Maximum size of words in bytes.\n");
    fprintf(fptr, "word_size=100\n\n");

    fprintf(fptr, "# Number of words in test.\n");
    fprintf(fptr, "test_length=25\n\n");

    fprintf(fptr, "# Seed for RNG, 0 for random.\n");
    fprintf(fptr, "seed=0");

    fclose(fptr);
}

int read_int(char *line) {
    int val;
    char param[255];
    sscanf(line, "%[^=]=%d\n", param, &val);
    return val;
}

void read_str(char *line, char *val) {
    char param[255];
    sscanf(line, "%[^=]=%s\n", param, val);
}

void parse_config(struct sconfig *config) {
    FILE *fptr;
    fptr = fopen(config->config_path, "r");
    char buff[255];

    if (fptr == NULL) {
        printf("aled\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(fptr)) {
        fgets(buff, 255, fptr);
        if (buff[0] == '#' || strlen(buff) < 4) continue;
    
        if (strstr(buff, "word_list_file")) read_str(buff, config->file_name);
    
        if (strstr(buff, "word_size")) config->word_size = read_int(buff);
        if (strstr(buff, "test_length")) config->test_length = read_int(buff);
        int seed = read_int(buff);
        if (strstr(buff, "seed")) (0 == seed) ? (config->seed = time(NULL)) : (config->seed = seed);

    }

    fclose(fptr);
}

void manage_config(struct sconfig *config) {
    get_path(config);

    if (access(config->config_path, F_OK) == 0) {
        parse_config(config);
    } else {
        create_config(config);
        parse_config(config);
    }
}