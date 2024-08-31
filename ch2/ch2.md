# 2. Operating System

process, process API, thread/multi-threaded, process states (ready/running/blocked), PCB, process list/table, address space, file, design goals, timesharing, batch, soft/hard real-time, service/user process, CPU/IO/Memory-bound processes, GNU, POSIX, bit/Byte, KB/MB/GB/TB/PB/EB, ms/us/ns, gcc

## 2.1 Introduction

The OS virtualises physical resources (i.e. make it accessible) so they become user friendly and easy
to use.

The OS is a **resource manager** that manages the hardware resources (CPU, memory and disk) of the computer.
The OS exports a few hundred **system calls** to allow users to interact with the OS.

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int
main(int argc, char *argv[])
{
 int *p = malloc(sizeof(int)); // a1
 assert(p != NULL);
 printf("(%d) address pointed to by p: %p\n",
 getpid(), p); // a2
 *p = 0; // a3
 while (1) {
  Spin(1);
  *p = *p + 1;
  printf("(%d) p: %d\n", getpid(), *p); // a4
 }
 return 0;
}
```
