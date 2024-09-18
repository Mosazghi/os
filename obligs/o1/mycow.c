#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pids[argc - 1];
  for (int i = 1; i < argc; i++) {

    if ((pids[i - 1] = fork()) == 0) {
      char *args[] = {"cowsay", argv[i], NULL}; // NULL to terminate the, cowsay
      // is the command to be executed for the program itself same as argv[0]
      execvp("cowsay", args);
      perror("execvp");
      exit(1);
    } else {
      // waitpid(pids[i - 1], NULL, 0);
    }
  }
  return 0;
}
