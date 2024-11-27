#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
sem_t sema;
int balance = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
  pthread_mutex_lock(&lock);
  balance++;
  printf("%s made balance: %d\n", (char *)arg, balance);
  pthread_mutex_unlock(&lock);
  sem_post(&sema);
  return NULL;
}
int main(void) {
  pthread_t thread;
  sem_init(&sema, 0, 0);
  pthread_create(&thread, NULL, worker, (void *)"Newthread");
  sem_wait(&sema);
  worker((void *)"Mainthread");
  pthread_join(thread, NULL);
  return 0;
}
