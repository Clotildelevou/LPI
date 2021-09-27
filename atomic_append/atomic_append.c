#include "atomic_append.h"

int main(int argc, char *argv[])
{
    int fd;

    if ((argc != 3 && argc != 4) || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "usage: ./a.out pathname\n");
        exit(-1);
    }

    if (argc == 3) {
        fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
            fprintf(stderr, "open\n");
            exit(-1);
        }

        for(int i = 0; i < atoi(argv[2]); i++)
        {
            if (write(fd, "\0", 1) == -1)
            {
                fprintf(stderr, "write\n");
                exit(-1);
            }
        }

    }
    else {
        fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
            fprintf(stderr, "open\n");
            exit(-1);
        }
        for(int i = 0; i < atoi(argv[2]); i++)
        {
            if (lseek(fd, 0, SEEK_END) == -1)
            {
                fprintf(stderr, "lseek\n");
                exit(-1);
            }
            if (write(fd, "\0", 1) == -1)
            {
                fprintf(stderr, "write\n");
                exit(-1);
            }
        }
    }

    if (close(fd) == -1)
    {
        fprintf(stderr, "close\n");
        exit(-1);
    }
    exit(0);
}
