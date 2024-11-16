#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid = fork();
  if (pid == 0) {
    printf("Child process\n");
    printf("Child process id: %d\n", getpid());
    printf("Parent process id: %d\n", getppid());
    exit(0);
  } else {
    wait(NULL);
    printf("Parent process\n");
    printf("Parent process id: %d\n", getpid());
    printf("Parent process id: %d\n", getppid());
  }
  return 0;
}
