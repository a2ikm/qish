#include "qish.h"
#include "qish_test.h"

void test_tokenize(void) {
  char **tokens = tokenize("foo");
  EXPECT_S("foo", tokens[0]);
  EXPECT_NULL(tokens[1]);
}

int main(int argc, char **argv) {
  test_tokenize();
}
