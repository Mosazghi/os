#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *ThreadOne(void *i) {
  printf("One!\n");
  return 0;
}

void *ThreadTwo(void *i) {
  printf("Two!\n");
  return 0;
}

void *ThreadThree(void *i) {
  printf("Three!\n");
  return 0;
}

int main(void) {
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, ThreadOne, NULL);
  pthread_mutex_lock(tid1);
  pthread_create(&tid2, NULL, ThreadTwo, NULL);
  pthread_mutex_lock(tid2);
  pthread_create(&tid3, NULL, ThreadThree, NULL);
  pthread_mutex_lock(tid3);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  return 0;
}
