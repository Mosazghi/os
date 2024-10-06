# 7 Threads and Locks

PCB vs TCB, single- vs multi-thread, pthread create/join, atomicity, critical section, race condition, deterministic, mutual exclusion, mutex lock, test-and-set, xchg, compare-and-swap, cmpxchg, lock prefix, spin/busy waiting, spin or switch, yield, two-phase lock

# 7.1 Introduction

A multi-threaded program has more than one point of execution (i.e., multiple
PCs)

Each thread is very much like a separate process, but sharing same address
space.

_Each thread has its own private set of registers it uses for computation_; thus, if there are two threads that are running on a single processor, when switching from running one (T1) to running the
other (T2), a context switch must take place. The context switch between
threads is quite similar to the context switch between processes, as the
register state of T1 must be saved and the register state of T2 restored
before running T2. With processes, we saved state to a process control
block (PCB); now, we’ll need one or more **thread control blocks (TCBs)** to store the state of each thread of a process.

We don't need to switch page table between threads because they share the same.

![multi-threaded-addr-space](assets/multi-threaded-addr-space.png)

^ Each thread has its own stack;

- Thus, any stack-allocated variables, parameters, return values, and other things that we put on the stack will be placed in
  what is sometimes called **thread-local storage**, i.e., the stack of the relevant thread
