#include <stdio.h>
#include <stdlib.h>
#define NITER 10000

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: memory-user <memory>\n");
    exit(EXIT_FAILURE);
  }

  int memory = atoi(argv[1]) * 1024 * 1024;
  int length = (int)(memory / sizeof(int));
  int *arr = malloc(memory);
  if (arr == NULL) {
    fprintf(stderr, "malloc failed\n");
  }
  for (int i = 0; i < NITER; i++) {
    for (int j = 0; j < length; j++)
      arr[j] += 1;
  }

  free(arr);
  return 0;
}
