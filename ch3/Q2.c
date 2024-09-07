#include <fcntl.h> // for open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for file permissions
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world (pid:%d)\n", (int)getpid());
  char *child_msg = "hello, I am child\n";
  char *parent_msg = "hello, I am parent\n";

  int fd = open("./Q2.output", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
  if (fd < 0) {
    perror("open");
    exit(1);
  }
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am child (pid:%d)\n", (int)getpid());
    write(fd, child_msg, strlen(child_msg));

    close(fd);

  } else {
    wait(NULL);
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
    write(fd, parent_msg, strlen(parent_msg));
    close(fd);
  }
  close(fd);

  return 0;
}

// Output:
// hello world (pid:12345)
// hello, I am child (pid:12346)
// Answer: The output to the file is as expected.
