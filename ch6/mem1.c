#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define S 1024 * 256

int main(void) {
  int size = S;

  printf("Creating array with %d elements\n", size);

  int *array = malloc(size * sizeof(int));

  pause();
}

/*
 *
 * Conclusion:
 *
 * The processes think they have VERT size memory, but in reality they do not
 * used everything they think they will use thus mem1_VIRT = mem2_VIRT
 *
 * This is the thequnique of demand paging, the memory is not allocated until it
 * is used
 *
 * However, in mem2.c, the array is initialized with values, so the memory is
 * used (initialized) and the memory is allocated, hence higher RES than mem1.c
 *
 *
 * The size difference is 2304 KB - 1280 KB = 1024 KB = 2*10 * 20 * 2^10 B =
 * 2^20 B = 1 MB -- which is the size of the array.
 */
