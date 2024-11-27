#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Fork failed!\n");
    exit(-1);
  } else if (rc == 0) {
    printf("hi im %s My PID is %i\n", argv[1], getpid());
    execl("/bin/date", "date");
  } else {
    wait(NULL);
  }
  return 0;
}
