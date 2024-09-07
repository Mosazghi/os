#include <fcntl.h> // for open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for file permissions
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int)getpid());
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    close(STDOUT_FILENO);
    printf("This will not be printed\n");
    exit(0);
  } else {
    wait(NULL);
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
  }
  return 0;
}
