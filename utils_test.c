#include <stdint.h>
#include "qish.h"
#include "qish_test.h"

void test_vec(void) {
  Vector *v = vec_new();
  EXPECT_I(0, v->len);

  for (int i = 0; i < 100; i++) {
    vec_push(v, (void *)(intptr_t)i);
  }

  EXPECT_I(100, v->len);
  EXPECT_I(0, (intptr_t)v->data[0]);
  EXPECT_I(2, (intptr_t)v->data[2]);
  EXPECT_I(50, (intptr_t)v->data[50]);
  EXPECT_I(99, (intptr_t)v->data[99]);

  vec_free(v);
}

int main(int argc, char **argv) {
  test_vec();
  return 0;
}
