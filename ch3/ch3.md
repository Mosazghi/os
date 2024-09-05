# 3. System Calls

fork, copy-on-write, exec, wait, signal, limited direct execution, instructions/system calls/commands, kernel mode, user mode, mode switch/transition, preemptive multitasking, trap table (interrupt vector table), sync/async interrupts, software/exception/hardware interrupt, timer interrupt, Process ID (PID), (call) stack, kernel stack, privileged operation/instruction, cooperative vs preemptive (timer interrupt)

## 3.1 System Calls

Using `fork()`and `exec()` system calls to create a new process and run a program in it. The `wait()` system call is used to wait for the child process to complete.

### 3.1.1 fork()

> Creates a new process

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello (pid:%d)\n", (int) getpid());
  int rc = fork();

  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    printf("child (pid:%d)\n", (int) getpid());
  } else {
    // parent goes down this path (main)
    printf("parent of %d (pid:%d)\n",
    rc, (int) getpid());
  }
  return 0;
 }
```

```
prompt> ./p1
hello (pid:29146)
parent of 29147 (pid:29146)
child (pid:29147)
prompt>
```

Note that the parent receives the child's process ID from the `fork()` system call. The child receives `0` from the `fork()` system call, hence printing "child...". One can then use this to write code that is executed by the child process.

`fork()` uses **copy-on-write** to avoid allocating memory unnecessarily. Copy-on-write
means that the new process can just keep using the memory of the parent process as
long as both processes just issues reads. As soon as one of them issues a write, then the
two processes need their own private copy.

### 3.1.2 wait()

> Waits for the child process to complete and execute remaining code of the parent process

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("hello (pid:%d)\n", (int) getpid());
  int rc = fork();

  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    printf("child (pid:%d)\n", (int) getpid());
  } else { // parent goes down this path
    int rc_wait = wait(NULL);
    printf("parent of %d (rc_wait:%d) (pid:%d)\n",
    rc, rc_wait, (int) getpid());
  }
  return 0;
}
```

`prompt> ./p2
hello (pid:29266)
child (pid:29267)
parent of 29267 (rc_wait:29267) (pid:29266)
prompt>`

That way we can always ensure that the parent process waits for the child process to complete.

### 3.1.3 exec()

> Replaces the current process with a new program

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("hello (pid:%d)\n", (int) getpid());
  int rc = fork();

  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) { // child (new process)
    printf("child (pid:%d)\n", (int) getpid());
    char *myargs[3];
    myargs[0] = strdup("wc"); // program: "wc"
    myargs[1] = strdup("p3.c"); // arg: input file
    myargs[2] = NULL; // mark end of array
    execvp(myargs[0], myargs); // runs word count
    printf("this shouldn’t print out");
  } else { // parent goes down this path
    int rc_wait = wait(NULL);
    printf("parent of %d (rc_wait:%d) (pid:%d)\n",
    rc, rc_wait, (int) getpid());
  }
  return 0;
}
```

`prompt> ./p3
hello (pid:29383)
child (pid:29384)
29 107 1030 p3.c
parent of 29384 (rc_wait:29384) (pid:29383)
prompt>`

Here, it **loads** code (and static data) from the given executable (`wc`)
and **overwrites** the current code segment (and current static data) with
it; essentially re-initializing the process with the new program.
