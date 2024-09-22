#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int x = 3;
  int *y = malloc(100);
  printf("x is at : %p\n", &x);
  printf("y is at : %p\n", y);
  x = y[1000];
  printf("x is : %d\n", x);
  return 0;
}
