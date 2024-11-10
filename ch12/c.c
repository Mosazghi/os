#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char buff[5];
  if (argc != 2) {
    printf("Need an argument!\n");
    exit(1);
  }
  strlcpy(buff, argv[1], sizeof(buff));
  printf("\nYou typed [%s]\n\n", buff);
  return (0);
}
