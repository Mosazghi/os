#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t rc = fork();
  if (rc < 0) {
    fprintf(stderr, "FORKING FAILED!\n");
  } else if (rc == 0) {
    printf("Addr of stack data: %p\n", main);
  } else {
    wait(NULL);
    printf("Addr of heap data: %p", malloc(100e6));
  }
}
