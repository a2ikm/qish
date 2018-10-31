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

void test_sb(void) {
  StringBuilder *sb;

  sb = sb_new();
  EXPECT_I(0, strlen(sb_flush(sb)));

  sb = sb_new();
  sb_add(sb, 'f');
  sb_add(sb, 'o');
  sb_add(sb, 'o');
  sb_add(sb, 'b');
  sb_add(sb, 'a');
  sb_add(sb, 'r');
  EXPECT_S("foobar", sb_flush(sb));
}

int main(int argc, char **argv) {
  test_vec();
  test_sb();
  return 0;
}
