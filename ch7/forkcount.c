#include <stdio.h>     /* printf */
#include <stdlib.h>    /* exit */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <unistd.h>    /* fork */

int g_ant = 0; /* global declaration */

void writeloop(char *text) {
  long i = 0;
  while (g_ant < 30) {
    if (++i % 100000 == 0) {
      printf("%s: %d\n", text, ++g_ant);
    }
  }
}

int main(void) {
  pid_t pid;

  pid = fork();
  if (pid == 0) { /* child */
    writeloop("Child");
    exit(0);
  }
  writeloop("Parent"); /* parent */
  waitpid(pid, NULL, 0);
  return 0;
}
