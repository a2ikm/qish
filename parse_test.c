#include "qish.h"
#include "qish_test.h"

void test_tokenize(void) {
  char **tokens;

  tokens = tokenize("foo");
  EXPECT_S("foo", tokens[0]);
  EXPECT_NULL(tokens[1]);
  free(tokens);

  tokens = tokenize("foo bar");
  EXPECT_S("foo", tokens[0]);
  EXPECT_S("bar", tokens[1]);
  EXPECT_NULL(tokens[2]);
  free(tokens);
}

int main(int argc, char **argv) {
  test_tokenize();
}
