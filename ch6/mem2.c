#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define S 1024 * 256

int main(void) {
  int i, size = S;

  printf("Creating array with %d elements\n", size);

  int *array = malloc(size * sizeof(int));

  for (i = 0; i < size; i++) {
    array[i] = i;
  }

  pause();
}
