#include <stdio.h>
#include <stdlib.h>
#define STR_LENGTH 10
typedef struct {
  int a;
  int b;
} my_struct_t;

void test1(my_struct_t s) {
  s.a = 1;
  s.b = 2;
}

void test2(my_struct_t *s) {
  s->a = 1;
  s->b = 2;
}

int main() {
  my_struct_t s = {0, 0};
  my_struct_t *s2 = (my_struct_t *)malloc(sizeof(my_struct_t));
  test1(s);
  printf("s.a = %d, s.b = %d\n", s.a, s.b);
  test2(s2);
  printf("s2.a = %d, s2.b = %d\n", s2->a, s2->b);
  return 0;
}
