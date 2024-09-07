#include <stdio.h>     /* printf */
#include <stdlib.h>    /* exit */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <unistd.h>    /* fork */
/* Note: pid_t is probably just an int, but it might be different
   kind of ints on different platforms, so using pid_t instead of
   int helps makes the code more platform-independent
*/

void process(int number, int time) {
  printf("Process %d is running\n", number);
  sleep(time);
  printf("Process %d ran for %d seconds\n", number, time);
}

// Process schedule: Process number, start time, end time
int processes[6][3] = {
    {0, 0, 1}, // Process 0 runs from time 0 to 1
    {1, 1, 3}, // Process 1 runs from time 1 to 3
    {2, 0, 3}, // Process 2 runs from time 0 to 3
    {3, 3, 5}, // Process 3 runs from time 3 to 5
    {4, 1, 4}, // Process 4 runs from time 1 to 4
    {5, 4, 7}  // Process 5 runs from time 4 to 7
};

int main(void) {
  pid_t pids[6]; // Array to store process IDs
  int processed = 0;

  // Loop over time steps (processed represents the current time)
  while (processed <= 6) {
    // Fork processes whose start time matches the current time
    for (int i = 0; i < 6; i++) {
      if (processes[i][1] == processed) {
        pids[i] = fork();
        if (pids[i] == 0) {
          // In child process, call process function and then exit
          process(processes[i][0], processes[i][2] - processes[i][1]);
          exit(0);
        }
      }
    }
    // Increment time step
    processed++;
    sleep(1);
  }

  // Wait for all child processes to finish
  for (int i = 0; i < 6; i++) {
    waitpid(pids[i], NULL, 0);
  }

  return 0;
}
