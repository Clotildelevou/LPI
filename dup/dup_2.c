#include "dup_2.h"

int main(int argc, char *argv[])
{
    int newfd;

    if (strcmp(argv[1], argv[2]) == 0)
    {
        return atoi(argv[1]);
    }

    if (argc != 3)
        printf("usage: ./a.out oldfd newfd\n");

    if (fcntl(atoi(argv[1]),  F_GETFD) == -1)
    {
        fprintf(stderr, "Error on fcntl for oldfd\n");
        errno = EBADF;
        exit(-1);
    }

    newfd = fcntl(atoi(argv[1]), F_DUPFD, atoi(argv[2]));
    if (newfd == -1)
    {
        fprintf(stderr, "Error on fcntl in duplication\n");
        errno = EBADF;
        exit(-1);
    }

    if (close(atoi(argv[1])) == -1)
    {
        fprintf(stderr, "Error on closing file");
        errno = EBADF;
        exit(-1);
    }

    return newfd;
}
