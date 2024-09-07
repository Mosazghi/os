#include <fcntl.h> // for open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for file permissions
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  char buf;
  int fd[2];
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());

    if (pipe(fd) == -1) {
      fprintf(stderr, "pipe failed\n");
      exit(1);
    }
    int gc = fork();
    if (gc < 0) {
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if (gc == 0) {
      printf("hello, I am grandchild (pid:%d)\n", (int)getpid());
      write(fd[1], argv[1], strlen(argv[1]));

      exit(0);
    } else {
      wait(NULL);
      close(fd[1]);
      while (read(fd[0], &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
      }

      write(STDOUT_FILENO, "\n", 1);
      close(fd[0]);
      exit(0);
    }

    exit(0);
  } else {
    wait(NULL);
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
  }
  return 0;
}
