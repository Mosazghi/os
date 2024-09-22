#include <stdio.h>
#include <stdlib.h>

int main() {
  int *data = malloc(100 * sizeof(int));
  free(data);
  printf("elem: %d\n", data[0]);
  return 0;
}
