#include "o_append.h"

int main(int argc, char *argv[])
{
    int fd;
    off_t off;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        printf("usage: ./a.out pathname\n");

    fd = open(argv[1], O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        printf("open\n");
        exit(-1);
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        printf("lseek\n");
        exit(-1);
    }

    if (write(fd, "test", 4) == -1)
    {
        printf("write\n");
        exit(-1);
    }

    exit(0);
}
