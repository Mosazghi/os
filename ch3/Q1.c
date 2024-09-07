#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int)getpid());
  int x = 100;
  int rc = fork();
  printf("rc is %d\n", rc);
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc) {
    // printf("rc is %d\n", rc);

    printf("ddBefore x is %d child\n", x);
    x = 200;
    // child (new process)
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    printf("after x is %d child\n", x);

  } else {
    wait(NULL);
    printf("Before x is %d parent\n", x);
    x = 300;
    // parent goes down this path (original process)
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
    printf("after x is %d parent\n", x);
  }
  printf("hell i m unkown %d\n", (int)getpid());
  return 0;
}

// Answer: They will have their own cpoy of the variables. The child will have a
// copy of the parent's variables. They will not share the same memory space.
