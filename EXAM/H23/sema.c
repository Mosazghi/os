#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
sem_t s;
sem_t s2;

void *ThreadOne(void *i) {
  printf("One!\n");
  sem_post(&s);
  return 0;
}

void *ThreadTwo(void *i) {
  sem_wait(&s);
  printf("Two!\n");
  sem_post(&s2);
  return 0;
}

void *ThreadThree(void *i) {
  sem_wait(&s2);
  printf("Three!\n");
  return 0;
}

int main(void) {
  pthread_t tid1, tid2, tid3;
  sem_init(&s, 0, 0);
  sem_init(&s2, 0, 0);
  pthread_create(&tid1, NULL, ThreadOne, NULL);
  pthread_create(&tid2, NULL, ThreadTwo, NULL);
  pthread_create(&tid3, NULL, ThreadThree, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  return 0;
}
