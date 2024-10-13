#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g_ant = 0;                                  /* global declaration */
pthread_mutex_t lock;                           /* mutex declaration */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; /* condition variable */
int turn = 0; /* turn variable: 0 for main, 1 for thread */

void *writeloop(void *arg) {
  char *msg = (char *)arg;

  while (g_ant < 10) {
    pthread_mutex_lock(&lock); /* lock the mutex */

    while ((turn == 0 && msg != "main") || (turn == 1 && msg != "thread")) {
      pthread_cond_wait(&cond, &lock); /* wait for the right turn */
    }
    if (g_ant == 10) {
      pthread_mutex_unlock(&lock); /* unlock the mutex */
      break;
    }
    g_ant++;
    usleep(rand() % 10); /* small random delay */
    printf("%s: %d\n", msg, g_ant);

    /* Switch turn after printing */
    turn = (msg == "main") ? 1 : 0;

    pthread_cond_signal(&cond);  /* signal the other thread */
    pthread_mutex_unlock(&lock); /* unlock the mutex */
  }

  return NULL;
}

int main(void) {
  pthread_t tid;

  pthread_mutex_init(&lock, NULL); /* initialize the mutex */

  /* Create a new thread for writeloop */
  pthread_create(&tid, NULL, writeloop, (void *)"thread");
  writeloop("main"); /* main thread also runs writeloop */

  pthread_join(tid, NULL); /* wait for the new thread to finish */

  pthread_mutex_destroy(&lock); /* destroy the mutex */
  pthread_cond_destroy(&cond);  /* destroy the condition variable */

  return 0;
}
