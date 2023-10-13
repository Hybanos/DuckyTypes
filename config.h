struct sconfig {
    char *path;
    char *config_path;
    char file_name[100];
    int list_size;
    int word_size;
    int test_length;
};

void manage_config(struct sconfig *);