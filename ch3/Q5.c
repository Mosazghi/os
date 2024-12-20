#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int status;

  // Create a child process
  pid = fork();

  if (pid < 0) {
    // Error occurred during fork
    perror("fork failed");
    exit(1);
  } else if (pid == 0) {
    printf("Child process (PID: %d) trying to wait for its child (but has "
           "none)\n",
           getpid());
    wait(NULL); // This will fail because the child has no child processes
    perror("Child wait failed"); // This will print an error message
    exit(0);
  } else {

    // Parent process
    printf("Parent process (PID: %d) is waiting for child to finish\n",
           getpid());

    // Parent waits for the child process to finish
    pid_t child_pid = waitpid(pid, &status, 0);

    if (child_pid == -1) {
      perror("wait failed");
    } else {
      printf("Parent: Child process with PID %d finished\n", child_pid);

      // Check if the child exited normally
      if (WIFEXITED(status)) {
        printf("Child exited with status %d\n", WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("Child was killed by signal %d\n", WTERMSIG(status));
      }
    }
  }

  return 0;
}
