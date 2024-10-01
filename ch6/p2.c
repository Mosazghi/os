#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <ARRAY_SIZE>\n", argv[0]);
    return 1;
  }

  char *endptr;
  long long ARRAY_SIZE = strtol(argv[1], &endptr, 10);
  if (*endptr != '\0') {
    fprintf(stderr, "Invalid input: %s\n", argv[1]);
    return 1;
  }

  if (ARRAY_SIZE < 1 || ARRAY_SIZE > 400000000) {
    fprintf(stderr, "Number must be between 1 and 400M\n");
    return 1;
  }

  int i;
  int *array = malloc(sizeof(int) * ARRAY_SIZE);
  int *random_index = malloc(sizeof(int) * ARRAY_SIZE);
  double elapsed_time;
  clock_t start, end;

  srand(time(NULL));

  // Initialize the array with random values and create random indices
  for (i = 0; i < ARRAY_SIZE; i++) {
    array[i] = rand();
    random_index[i] = rand() % ARRAY_SIZE;
  }

  // Perform sequential accesses
  start = clock();
  for (i = 0; i < 10000000; i++) {
    array[i % ARRAY_SIZE]++; // Access an element in sequence
  }
  end = clock();

  elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Elapsed time sequential: %.6f seconds\n", elapsed_time);

  // Perform random accesses
  start = clock();
  for (i = 0; i < 10000000; i++) {
    array[random_index[i % ARRAY_SIZE]]++; // Access a random element
  }
  end = clock();

  elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Elapsed time random: %.6f seconds\n", elapsed_time);

  free(array);
  free(random_index);
  return 0;
}

/*
 *  Ved 4_000_000 * 4 = 16_000_000 (16MB) ser jeg redusert i hastighet fordi den
 *  nærmerer seg L3 cache som er 18MB.
 *
 *  Ved 40_000_000 * 4 = 160_000_000 (160MB) ser jeg kraftig redusert hastighet
 *  fordi den er langt over L3 cache (som betry at den må fetche fra memory).
 *
 * */
