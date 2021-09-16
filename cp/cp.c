#include "cp.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024

#endif

int main(int argc, char *argv[])
{
  int fd_src, fd_dest;
  ssize_t num_read;
  char buf[BUF_SIZE];

  if (argc != 3)
  {
    printf("Usage : cp src dest\n");
    exit(-1);
  }

  fd_src = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);
  if (fd_src == -1)
  {
    printf("Failed to open %s\n", argv[1]);
    exit(-1);
  }

  fd_dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
  if (fd_dest == -1)
  {
    printf("Failed to open %s\n", argv[2]);
    exit(-1);
  }

  while((num_read = read(fd_src, buf, BUF_SIZE)) > 0)
  {
    if (write(fd_dest, buf, num_read) != num_read)
    {
      printf("write() error or partial write occured\n");
      exit(-1);
    }
  }

  if (num_read == -1)
  {
    printf("Error on reading %s\n", argv[1]);
    exit(-1);
  }

  if (close(fd_src) == -1)
  {
    printf("Error on close %s\n", argv[1]);
    exit(-1);
  }

  if (close(fd_dest) == -1)
  {
    printf("Error on close %s\n", argv[2]);
    exit(-1);
  }

  return 0;

}
