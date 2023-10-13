#include <unistd.h>

#include "config.h"
#include "consts.h"

char * get_path(struct sconfig *config) {
    char *path = calloc(sizeof(char), 255);
    readlink("/proc/self/exe", path, 255);

    for (int i = strlen(path); i > 0; i --) {
        if (path[i - 1] == '/') {
            path[i] = 0;
            break;
        }
    }
    
    printf("path : %s\n\n", path);
    config->path = path;
    config->config_path = calloc(sizeof(char), 255);
    strcat(config->config_path, config->path);
    strcat(config->config_path, "config.conf");
    return path;
}

void create_config(struct sconfig *config) {
    FILE *fptr;

    fptr = fopen(config->path, "w");
    fprintf(fptr, "# File to read words from.\n");
    fprintf(fptr, "word_list_file=words_fr.txt\n\n");

    fprintf(fptr, "# Number of words to be selected from file.\n");
    fprintf(fptr, "list_size=1500\n\n");

    fprintf(fptr, "# Maximum size of words in bytes.\n");
    fprintf(fptr, "word_size=100\n\n");

    fprintf(fptr, "# Number of words in test.\n");
    fprintf(fptr, "test_length=25");

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
        // printf(buff);
        if (buff[0] == '#' || strlen(buff) < 4) continue;
    
        if (strstr(buff, "word_list_file")) read_str(buff, config->file_name);
    
        if (strstr(buff, "list_size")) config->list_size = read_int(buff);
        if (strstr(buff, "word_size")) config->word_size = read_int(buff);
        if (strstr(buff, "test_length")) config->test_length = read_int(buff);
    
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