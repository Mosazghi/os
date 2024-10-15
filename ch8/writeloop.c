#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g_ant = 0;
pthread_mutex_t lock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int turn = 0;

void *writeloop(void *arg) {
  char *msg = (char *)arg;

  pthread_mutex_lock(&lock);
  while (g_ant < 10) {

    // while ((turn == 0 && msg != "main") || (turn == 1 && msg != "thread")) {
    //   pthread_cond_wait(&cond, &lock);
    // }
    if (g_ant == 10) {
      pthread_mutex_unlock(&lock);
      break;
    }
    g_ant++;
    usleep(rand() % 10);
    printf("%s: %d\n", msg, g_ant);

    turn = (msg == "main") ? 1 : 0;

    // pthread_cond_signal(&cond);
    // --> mutex unlock
  }

  pthread_mutex_unlock(&lock);

  return NULL;
}

int main(void) {
  pthread_t tid;

  pthread_mutex_init(&lock, NULL);

  pthread_create(&tid, NULL, writeloop, (void *)"thread");
  writeloop("main");

  pthread_join(tid, NULL);

  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);

  return 0;
}
