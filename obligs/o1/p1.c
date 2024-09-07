#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int c = 5;
  pid_t pid = fork();
  if (pid == 0) {
    c += 5;
  } else {
    pid = fork();
    c += 10;
    if (pid) {
      c += 10;
    }
  }
  fork();
  printf("%d by (pid=%d)\n", c, getpid());
  return 0;
}
