#include "dup_2.h"

int main(int argc, char *argv[])
{
    int newfd;
    if (argc != 3)
        printf("usage: ./a.out oldfd newfd\n");

    if (fcntl(atoi(argv[2]),  F_GETFD) != -1)
    {
        if (close(atoi(argv[2])) == -1)
        {
            fprintf(stderr, "Error on closing file");
            errno = EBADF;
            exit(-1);
        }
    }

    newfd = fcntl(atoi(argv[1]), F_DUPFD, atoi(argv[2]));
    if (newfd == -1)
    {
        fprintf(stderr, "Error on fcntl\n");
        errno = EBADF;
        exit(-1);
    }

    return newfd;
}
