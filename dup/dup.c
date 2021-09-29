#include "dup.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        printf("usage: ./a.out fd_to_duplicate\n");

    return fcntl(atoi(argv[1]), F_DUPFD, 0);
}
