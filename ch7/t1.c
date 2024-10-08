#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int counter = 0;
pthread_mutex_t lock;

void *mythread(void *arg) {
  printf("%s: begin\n", (char *)arg);

  if (pthread_mutex_lock(&lock) != 0) {
    fprintf(stderr, "Error locking mutex\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 1e7; i++) {
    counter = counter + 1;
  }

  if (pthread_mutex_unlock(&lock) != 0) {
    fprintf(stderr, "Error unlocking mutex\n");
    exit(EXIT_FAILURE);
  }

  printf("%s: done\n", (char *)arg);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;

  if (pthread_mutex_init(&lock, NULL) != 0) {
    fprintf(stderr, "Error initializing mutex\n");
    return EXIT_FAILURE;
  }

  printf("main: begin (counter = %d)\n", counter);

  if (pthread_create(&p1, NULL, mythread, "A") != 0) {
    fprintf(stderr, "Error creating thread A\n");
    return EXIT_FAILURE;
  }

  if (pthread_create(&p2, NULL, mythread, "B") != 0) {
    fprintf(stderr, "Error creating thread B\n");
    return EXIT_FAILURE;
  }

  if (pthread_join(p1, NULL) != 0) {
    fprintf(stderr, "Error joining thread A\n");
    return EXIT_FAILURE;
  }

  if (pthread_join(p2, NULL) != 0) {
    fprintf(stderr, "Error joining thread B\n");
    return EXIT_FAILURE;
  }

  if (pthread_mutex_destroy(&lock) != 0) {
    fprintf(stderr, "Error destroying mutex\n");
    return EXIT_FAILURE;
  }

  printf("main: done with both (counter = %d)\n", counter);
  return 0;
}
