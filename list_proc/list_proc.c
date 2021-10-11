#include "list_proc.h"

char *build_path(char *dirname)
{
    char *status = "/status";
    char *path = malloc(sizeof(dirname) + sizeof(status));
    strcpy(path, dirname);
    strcat(path, status);
    return path;
}

size_t get_size(int fd)
{
    //get the size
    ssize_t size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        perror("Couldn't get size\n");
        exit(-1);
    }
    //put the seeking head at the beginning of the file
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("Error on seek\n");
        exit(-1);
    }
    return size;
}

char *get_name(FILE *file)
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    line_size = getline(&line_buf, &line_buf_size, file);
    char *start = strstr(line_buf, "Name:");
    start += 4;

    char *end = start;
    while(strcmp(end, "\n") != 0)
    {
        end++;
    }
    size_t size = start - end;
    char *name = malloc(size);
    strncpy(start, name, size);
    line_size = line_size;
    line_count = line_count;
    return name;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "format: ./a.out username\n");
        exit(-1);
    }

    DIR *folder;
    struct dirent *entry;

    folder = opendir("/proc");
    if (folder == NULL)
    {
        perror("Unable to read directory");
        exit(-1);
    }

    while((entry = readdir(folder)))
    {
        if (entry->d_type == DT_DIR)
        {
            char *path = build_path(entry->d_name);
            FILE *file = fopen(path, "r");
            if (file == NULL)
            {
                perror("Couldn't open file");
                exit(-1);
            }
            char *name = get_name(file);
            printf("File : %s\n", name);

            free(name);
            free(path);
            fclose(file);
        }
    }

    argv = argv;
}