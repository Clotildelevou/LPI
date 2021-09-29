#include "check_dup.h"

int main(int argc, char *argv[])
{
    int flags1;
    int flags2;

    int offset1;
    int offset2;

    if (argc != 3)
    {
        printf("usage: ./a.out fd1 fd2\n");
        exit(-1);
    }

    flags1 = fcntl(atoi(argv[1]), F_GETFL);
    if (flags1 == -1)
    {
        perror("error on flags1");
        exit(-1);
    }

    flags2 = fcntl(atoi(argv[2]), F_GETFL);
    if (flags2 == -1)
    {
        perror("error on flags2");
        exit(-1);
    }

    offset1 = lseek(atoi(argv[1]), 0, SEEK_CUR);
    if (offset1 == -1)
    {
        perror("error on offset1");
        exit(-1);
    }

    offset2 = lseek(atoi(argv[2]), 0, SEEK_CUR);
    if (offset2 == -1)
    {
        perror("error on offset2");
        exit(-1);
    }

    if (flags1 == flags2
    &&  offset1 == offset2)
    {
        return 0;
    }
    else
        return -1;
}
