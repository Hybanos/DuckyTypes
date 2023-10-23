struct sconfig {
    char *path;
    char *config_path;
    char file_name[100];
    int list_size;
    int word_size;
    int test_length;
    int seed;
    char *test_bg_color[7];
    char *reset_bg_color[7];
};

void manage_config(struct sconfig *);