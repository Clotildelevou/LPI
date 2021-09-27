# the_k

Linux programming interface book exercises
- **tee** : tee command with -a option and --help


- **cp** : cp command


- **large file** : compile with **-D_FILE_OFFSET_BITS=64** flag or define the **_FILE_OFFSET_BITS** macro set to 64.


- **o_append** : A  program that  opens  an existing file  for writing  with the O_APPEND flag, and
  then  seeks  to  the  beginning  of  the  file  before  writing  some  data.


- **atomic_append** : This exercise is designed to demonstrate why the atomicity guaranteed by opening
  a  file  with  the  O_APPEND  flag  is  necessary.  Write  a  program  that  takes  up  to  three
  command-line arguments:
- ```
  $ atomic_append filename num-bytes [x]
  ```
  This  file  should  open  the  specified  filename  (creating  it  if  necessary)  and  append
  num-bytes  bytes  to  the  file  by using  write() to write  a byte  at a time. By default, the
  program  should  open  the  file  with  the  **O_APPEND**  flag,  but  if  a  third  command-line
  argument (x) is supplied, then the O_APPEND flag should be omitted, and instead the
  program  should  perform  an  lseek( fd,  0,  SEEK_END)  call  before  each  write().  Run
  two  instances  of  this  program  at  the  same  time  without  the  x  argument  to  write
  1 million bytes to the same file:
- ```
  $ atomic_append f1 1000000 & atomic_append f1 1000000
  ```
  Repeat  the  same  steps,  writing  to  a  different  file,  but  this  time  specifying  the  x
  argument:
- ```
  $ atomic_append f2 1000000 x & atomic_append f2 1000000 x
  ```

  List the sizes of the files f1 and f2 using ls –l and explain the difference.

```shell
[cloture@strix:~/Documents/Travail/Projets/the_k/atomic_append]$ gcc -Wall -Werror -Wextra -pedantic -std=c99 atomic_append.c
[cloture@strix:~/Documents/Travail/Projets/the_k/atomic_append]$ ./a.out f1 10000000 & ./a.out f1 10000000
[cloture@strix:~/Documents/Travail/Projets/the_k/atomic_append]$ ./a.out f2 10000000 x & ./a.out f2 10000000 x
[cloture@strix:~/Documents/Travail/Projets/the_k/atomic_append]$ ls -l
-rwxrwxr-x 1 cloture cloture    17032 sept. 27 21:24 a.out
-rw-rw-r-- 1 cloture cloture     1283 sept. 27 21:24 atomic_append.c
-rw-rw-r-- 1 cloture cloture      213 sept. 27 20:54 atomic_append.h
-rw------- 1 cloture cloture 20000000 sept. 27 21:26 f1
-rw------- 1 cloture cloture 10148463 sept. 27 21:27 f2
```

Because  the  combination  of  lseek()  plus  write()  is  not  atomic,  one  instance  of  the
program sometimes overwrote bytes written by the other instance. As a result, the file
f2 contains less than 2 million bytes.
