#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // int rc = fork();
  register int rax asm("rax");
  printf("eax: %d", rax);
  // if (rc < 0) {
  //   // fork failed; exit
  //   fprintf(stderr, "fork failed\n");
  //   exit(1);
  // } else if (rc == 0) {
  //   // child: redirect standard output to a file
  //   close(STDOUT_FILENO);
  //   open("./p1.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  //
  //   // now exec "wc"...
  //   char *myargs[3];
  //   myargs[0] = strdup("wc");   // program: "wc" (wor count)
  //   myargs[1] = strdup("Q4.c"); // argument: file to count
  //   myargs[2] = NULL;           // marks end of array
  //   execvp(myargs[0], myargs);  // runs word count
  // } else {
  //   // parent goes down this path (original process)
  //   int wc = wait(NULL);
  //   assert(wc >= 0);
  //   execvp("less", "./p1.output");
  // rax}
  return 0;
}
