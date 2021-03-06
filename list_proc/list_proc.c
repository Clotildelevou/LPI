#include "list_proc.h"

char *build_path(char *dirname)
{
    char *proc = "/proc/";
    char *status = "/status";
    char *path = malloc(sizeof(dirname) + sizeof(proc) + sizeof(status));
    strcpy(path, proc);
    strcat(path, dirname);
    strcat(path, status);
    printf("%s\n", path);
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
    char *name = malloc(size + 1);
    strncpy(start, name, size);
    line_size = line_size;
    line_count = line_count;
    strcpy(&name[size + 1], "\0");
    return name;
}

long get_uid(FILE *file)
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    line_size = getline(&line_buf, &line_buf_size, file);
    char *start = strstr(line_buf, "Uid:");
    start += 3;

    char *end = start;
    while(strcmp(end, "\n") != 0)
    {
        end++;
    }
    size_t size = start - end;
    char *uid = malloc(size + 1);
    strncpy(start, uid, size);
    line_size = line_size;
    line_count = line_count;
    strcpy(&uid[size + 1], "\0");
    return strtol(uid, NULL, 10);
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
        perror("Unable to open directory");
        exit(-1);
    }

    while(1)
    {
        entry = readdir(folder);
        errno = 0;
        if (entry == NULL) {
            if (errno != 0)
                perror("Unable to read directory");
            else
                break;
        }

        if (entry->d_type != DT_DIR || !isdigit((unsigned char) entry->d_name[0]))
            continue;

        char *path = build_path(entry->d_name);
        FILE *file = fopen(path, "r");
        if (file == NULL)
        {
            perror(path);
            continue;
        }

        char *name = get_name(file);
        long uid = get_uid(file);
        printf("File : %s, uid : %ld\n", name, uid);
        free(name);
        free(path);
        fclose(file);
        printf("PID : %s\n", entry->d_name);
    }

    argv = argv;
}