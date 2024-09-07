#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {

    printf("Hello ");
  } else {
    for (int i = 0; i < 1000000; i++) {
    }
    printf("Goodbye\n");
  }
  return 0;
}

// Answer this way the child will print first.
