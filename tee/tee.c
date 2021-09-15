#include "tee.h"


#ifndef BUF_SIZE
#define BUF_SIZE 1024

#endif

int main(int argc, char *argv[])
{
  char *filename;
  int fdfile;
  ssize_t num_read;
  int a_opt = 0;
  char buf[BUF_SIZE];

  if (argc > 3 || argc < 2 || strcmp(argv[1], "--help") == 0)
  {
    printf("Usage : {-a} filename\n");
    exit(-1);
  }

  if (argc == 2)
    filename = argv[1];
  else
  {
    filename = argv[2];
    if (strcmp(argv[1], "-a") == 0)
      a_opt = 1;
    else
    {
      printf("Usage : {-a} filename\n");
      exit(-1);
    }
  }

  if (a_opt == 1)
  {
    fdfile = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fdfile == -1)
    {
      printf("open\n");
      exit(-1);
    }
  }
  else
  {
    fdfile = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdfile == -1)
    {
      perror("open\n");
      exit(-1);
    }
  }

  while((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
  {
    printf("%s", buf);
    if (write(fdfile, buf, num_read) != num_read)
    {
      printf("write() error or partial write occured\n");
      exit(-1);
    }
  }
  if (num_read == -1)
  {
    printf("read");
    exit(-1);
  }

  if (close(fdfile) == -1)
  {
    printf("close\n");
    exit(-1);
  }

  return 0;
}
