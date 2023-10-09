#include "config.h"

#include <unistd.h>

struct sconfig {
    char file_name[100];
    int list_size;
    int word_size;
    int test_length;
};

void create_config() {
    FILE *fptr;

    fptr = fopen("config.conf", "w");
    fprintf(fptr, "# File to read words from.\n");
    fprintf(fptr, "word_list_file=words_fr.txt\n\n");

    fprintf(fptr, "# Number of words to be selected from file.\n");
    fprintf(fptr, "list_size=1500\n\n");

    fprintf(fptr, "# Maximum size of words in bytes.\n");
    fprintf(fptr, "word_size=100\n\n");

    fprintf(fptr, "# Number of words in test.\n");
    fprintf(fptr, "test_length=25\n\n");

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

void parse_config() {
    FILE *fptr;
    fptr = fopen("config.conf", "r");
    char buff[255];

    if (fptr == NULL) {
        printf("aled");
        exit(EXIT_FAILURE);
    }

    struct sconfig config;

    while (!feof(fptr)) {
        fgets(buff, 255, fptr);
        printf(buff);
        if (buff[0] == '#' || strlen(buff) < 4) continue;
    
        if (strstr(buff, "word_list_file")) read_str(buff, config.file_name);
    
        if (strstr(buff, "list_size")) config.list_size = read_int(buff);
        if (strstr(buff, "word_size")) config.word_size = read_int(buff);
        if (strstr(buff, "test_length")) config.test_length = read_int(buff);
    
    }

    printf("%s\n", config.file_name);
    printf("%d\n", config.list_size);
    printf("%d\n", config.word_size);
    printf("%d\n", config.test_length);
    
    fclose(fptr);
}

void manage_config() {
    if (access("config.conf", F_OK) == 0) {
        parse_config();
    } else {
        create_config();
    }
}